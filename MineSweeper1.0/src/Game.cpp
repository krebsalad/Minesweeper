#include "./../include/Game.h"
#include "./../include/uNode.h"
#include "./../include/Display.h"

#include <algorithm>
#include <iostream>

namespace Minesweeper
{
    Game::Game(int sx, int sy, Display* _display)
        : size_x(sx), size_y(sy), display(_display)
    {

    }

    Game::~Game()
    {
        delete display;
    }

    bool Game::init()
    {
        bool succes = true;
        uNode::createNodes2d(size_x, size_y);
        generateMineChars();    
        updateNodeChars();
        succes = display->init();
        if(succes)
        {
            createDisplayNodes(); 
        }
        return succes;
    }

    void Game::run()
    {
        while(display->update())
        {
            //input values
            int input_val1 = 0;
            int input_val2 = 0;

            //ask for node to click
            //std::cout << "Game: Choose node to start game on\n";
            //std::cout << "Game: Type a value x: ";
            //std::cin >> input_val1;
            //std::cout << "\nGame: Type a value y: ";
            //std::cin >> input_val2;
            //std::cout << "\n";
            
            //get target node
            std::string targetNode = uNode::coordsToId(input_val1, input_val2);
            actionOnNode(targetNode);

            //draw nodes
            display->clear();
            display->draw();
            //printNodes();
        }

        return;
    }

    void Game::createDisplayNodes()
    {      
        //calculate data for drawing terrain like triangle strip
        const int width = size_x + 2;
        const int length = size_y + 2;
        const int vertices_index_offset = 2;
        const int indices_index_offset = 6;
        const int numOfVertices = width * length * vertices_index_offset;						
        const int numOfIndices = width * length * indices_index_offset;						

        //the ouput objects
        float* vertices = new float[numOfVertices];	
        unsigned int* indices = new unsigned int[numOfIndices];					

        //index counters
        int vCounter = 0;													
        int iCounter = 0;	

        //measurements of the to be draw square centeralize
        float scale = 0.1f;	
        float offset_x = ((width * scale)/2)*-1.0f;			
        float offset_y = ((length * scale)/2)*-1.0f;								

        //go through x y to create square for current node
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < length; y++)
            {
                //get indcies of current node by checking assiging index point below, right and diaganol
                int p2 = vCounter;

                int p1 = (vCounter >= length*vertices_index_offset) ? (vCounter) - (length * vertices_index_offset) : p2;

                int p4 = (y + 1 < length) ? (vCounter + vertices_index_offset) : p2;

                int p3 = (y + 1 < length && vCounter + vertices_index_offset >= length * vertices_index_offset) ? (vCounter + vertices_index_offset) - (length * vertices_index_offset) : p1;

                //set the indcies of current node
                //first triangle
                indices[iCounter] = p2;
                indices[iCounter + 1] = p1;
                indices[iCounter + 2] = p4;
                //second triangle
                indices[iCounter + 3] = p4;
                indices[iCounter + 4] = p1;
                indices[iCounter + 5] = p3;

                //add new vertice
                vertices[vCounter] = (x * scale) + offset_x;
                vertices[vCounter+1] = (y * scale) + offset_y;

                //go to indecies for next square
                iCounter += indices_index_offset;
                vCounter +=vertices_index_offset;
            }
        }
        
        //call to renderer to create and add buffers
        display->addStaticVertices2d("map", vertices, numOfVertices, indices, numOfIndices);
    }

    void Game::revealeNode(std::string target_node)
    {
        std::shared_ptr<uNode> node = uNode::getNodeShare(target_node);

        // reveale and mark node
        if(!node->marked)
        {
            //reveale node
            reveleadNodes.push_back(target_node);
            node->marked = true;
            
            // reavele adjacent nodes if possible
            revealeAdjacentNodes(target_node);
        }
    }

    void Game::revealeAdjacentNodes(std::string target_node)
    {
        uNode node = uNode::getNode(target_node);

        //loop through adjacent nodes
        for (std::list<std::string>::iterator adj_node_iter = node.adjacencyList.begin(); adj_node_iter != node.adjacencyList.end(); adj_node_iter++)
        {
           if(node.transform.z == 0)
           {
               revealeNode(*adj_node_iter);
           }
        }
    }

    bool Game::actionOnNode(std::string target_node)
    {
        //setup nodes
        uNode::unmarkAllNodes();

        //get target node
        std::cout << "Game: Open Node action on Node (" << target_node << ")" << std::endl;
        uNode node = uNode::getNode(target_node);

        //quit if already reaveled
        std::list<std::string>::iterator nodeId_iter = std::find (reveleadNodes.begin(), reveleadNodes.end(), target_node);

        if(nodeId_iter != reveleadNodes.end())
        {
            std::cout << "Game: node already revelead" << std::endl;
            return true;
        }

        //reveale node
        revealeNode(target_node);

        //quit if mine
        if(node.transform.z == -1)
        {
            std::cout << "Game: node revelead mine" << std::endl;
            return false;
        }

        return true;
    }

    void Game::generateMineChars()
    {
        //bomb vals
        int num_of_mines = 0;
        int max_num_of_mines = size_x * size_y / 10;

        //make sure all nodes are created
        bool createdNodes = false;

        //loop until all mines set
        while(num_of_mines < max_num_of_mines)
        {
            for (int x = 0; x < size_x; x++)
            {
                for(int y = 0; y < size_y; y++)
                {
                    //if not yet reached max bombs attempty to add one
                    if(num_of_mines < max_num_of_mines)
                    {
                        //get node
                        std::shared_ptr<uNode> node = uNode::getNodeShare(uNode::coordsToId(x, y));
                        if(node->transform.z == -1)
                        { 
                            continue;
                        }

                        //random mine chance
                        int randnum = rand() % 100;
                        if(randnum > 95)
                        {
                            node->transform.z = -1;
                            std::cout << "Game: added a mine at " << node->nodeId << std::endl; 
                            num_of_mines++;
                        }
                    }  
                }

                //quit exit
                if(num_of_mines >= max_num_of_mines)
                    break;
            }
        }
        std::cout << "Game: Generated mines, num of mines: " << max_num_of_mines << std::endl;
    }

    void Game::updateNodeChars()
    {
        std::list<std::string> nodes = uNode::getAllNodeIds();
        for (std::list<std::string>::iterator node_iter = nodes.begin(); node_iter != nodes.end(); node_iter++)
        {
            //get node
            std::shared_ptr<uNode> node = uNode::getNodeShare(*node_iter);
            if(node->transform.z == -1)
            { 
                continue;
            }

            int num_of_mines = 0;
            for (std::list<std::string>::iterator adj_iter = node->adjacencyList.begin(); adj_iter != node->adjacencyList.end(); adj_iter++)
            {
                //get node
                std::shared_ptr<uNode> adj_node = uNode::getNodeShare(*adj_iter);
                if(adj_node->transform.z == -1)
                {
                    num_of_mines++;
                }
            }

            node->transform.z = num_of_mines;
        }

            std::cout << "Game: Updated node characters " << std::endl;
    }

    void Game::printNodes()
    {
        std::string txt = "";
        int str_size_x = 12;
        int str_height = 4;

        for (int x = 0; x < size_x; x++)
        {
            //draw +----+----+ ... then new line to draw the node
            for(int y = 0; y < size_y; y++)
            {     
                txt += "+";
                for(int t = 0; t < (str_size_x-1); t++)
                    txt += "-";
            }
            txt += "+\n";
            
            //draw lines |stuff here|stuff here| ...
            for(int line = 0; line < str_height; line++)
            {
                for(int y = 0; y < size_y; y++)
                {
                    //find node in revealed nodes
                    std::string nodeId = uNode::coordsToId(x, y);
                    std::list<std::string>::iterator nodeId_iter = std::find (reveleadNodes.begin(), reveleadNodes.end(), nodeId);
                    
                    //always start with
                    std::string ntxt = "|";

                    //show node id on first line
                    if(line == 0)
                    {  
                        ntxt += nodeId;
                    }
                    
                    //print value if revealed
                    if(line == 1 && nodeId_iter != reveleadNodes.end())
                    {
                        ntxt += "    " + std::to_string((int)uNode::getNode(nodeId).transform.z);
                    }

                    //show revealed
                    if(line == 2 && nodeId_iter != reveleadNodes.end())
                    {
                        ntxt += "    ^";
                    }

                    //ensure the added text is a total of 7 string long (1 of which |)
                    txt += ntxt;
                    for(int t = 0; t < (str_size_x-ntxt.length()); t++)
                        txt += " ";
                }
                //end with | and new line
                txt += "|\n";
            }   
        }

        //draw final +----+----+ ... then new line
        for(int y =0; y < size_y; y++)
        {
            txt += "+";
            for(int t = 0; t < (str_size_x-1); t++)
                    txt += "-";
        }
        txt += "+\n"; 

        //print line
        std::cout << "\nGame: --nodes--\n" << txt.c_str();
    }
};