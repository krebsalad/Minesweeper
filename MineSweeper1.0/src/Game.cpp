#include "./../include/Game.h"
#include "./../include/uNode.h"
#include <algorithm>
#include <iostream>

namespace Minesweeper
{
    Game::Game(int sx, int sy)
        : size_x(sx), size_y(sy)
    {

    }

    void Game::init()
    {
        uNode::createNodes2d(size_x, size_y);
        generateMineChars();    
        updateNodeChars();
    }

    void Game::run()
    {
        //input values
        int input_val1;
        int input_val2;

        //ask for node to click
        std::cout << "(game) Choose node to start game on\n";
        std::cout << "(action) Type a value x: ";
        std::cin >> input_val1;
        std::cout << "\n(action) Type a value y: ";
        std::cin >> input_val2;
        std::cout << "\n";

        actionOnNode(uNode::coordsToId(input_val1, input_val2));
        printNodes();
        return;
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
        std::cout << "(event) Open Node action on Node (" << target_node << ")" << std::endl;
        uNode node = uNode::getNode(target_node);

        //quit if already reaveled
        std::list<std::string>::iterator nodeId_iter = std::find (reveleadNodes.begin(), reveleadNodes.end(), target_node);

        if(nodeId_iter != reveleadNodes.end())
        {
            std::cout << "(event) node already revelead" << std::endl;
            return true;
        }

        //reveale node
        revealeNode(target_node);

        //quit if mine
        if(node.transform.z == -1)
        {
            std::cout << "(event) node revelead mine" << std::endl;
            return false;
        }

        return true;
    }

    void Game::generateMineChars()
    {
        //bomb vals
        int num_of_mines = 0;
        int max_num_of_mines = 10;

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
        std::cout << "Generated mines, num of mines: " << max_num_of_mines << std::endl;
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

            std::cout << "(info) Updated node characters " << std::endl;
    }

    void Game::printNodes()
    {
        
        std::string txt = "";
        for (int x = 0; x < size_x; x++)
        {
            //(7 * size_y) + 1 ascci character to draw line end with newline
            for(int y =0; y < size_y; y++)
            {
                txt += "+---------";
            }
            txt += "+\n";
            

            //3 * new line ascci character 
            for(int line = 0; line < 3; line++)
            {

                //(7 * size_y) + 1 ascci character to draw line end with newline
                for(int y = 0; y < size_y; y++)
                {
                    //find node in revealed nodes
                    std::string nodeId = uNode::coordsToId(x, y);
                    std::list<std::string>::iterator nodeId_iter = std::find (reveleadNodes.begin(), reveleadNodes.end(), nodeId);
                    std::string ntxt = "|";

                    //get node to draw
                    if(line == 0)
                    {
                        
                        ntxt += ""+nodeId;
                    }
                    
                    //check if revelealed
                    if(line == 1 && nodeId_iter != reveleadNodes.end())
                    {
                        ntxt += "    " + std::to_string((int)uNode::getNode(nodeId).transform.z);
                    }

                    //check if revelealed
                    if(line == 2 && nodeId_iter != reveleadNodes.end())
                    {
                        ntxt += "    ^";
                    }

                    //ensure the added text is a total of 7 string long (1 of which |)
                    txt += ntxt;
                    for(int t = 0; t < (10-ntxt.length()); t++)
                        txt += " ";
                }
                txt += "|\n";
            }   
        }

        // draw last line
        for(int y =0; y < size_y; y++)
        {
            txt += "+------";
        }
        txt += "+\n"; 

        //print line
        std::cout << "\n(game) Nodes: \n" << txt.c_str();
    }
};