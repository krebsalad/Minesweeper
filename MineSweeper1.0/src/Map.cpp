#include "./../include/Map.h"
#include "./../include/Node.h"
#include <iostream>
#include <string>
#include <ctime> 
#include <cstdlib>

namespace Minesweeper
{
    Map::Map(int _sx, int _sy) 
        : size_x(_sx), size_y(_sy), max_num_of_mines(2)
    {
        srand (unsigned(time(0)));
    }

    Map::~Map()
    {
        nodes.clear(true);
    }      

    void Map::initNodes()
    {
        std::cout << "(info) Initalising map nodes" << std::endl; 
        // generate nodes and set adhacency list
        generateNodes();
        updateAdjacentNodes();

        // set charachters of node
        generateMineChars();
        updateNodeChars();

        std::cout << "(info) Done initalising map nodes" << std::endl; 
    }

    void Map::generateNodes()
    {
        for (int x = 0; x < size_x; x++)
        {
            for(int y = 0; y < size_y; y++)
            {
                //create new node
                Node* node = new Node(x, y);

                if(nodes.addNode(node))
                {
                    node->myChar = "0";
                    std::cout << "(verbose) created node: Node (" << x << "," << y << ")" << std::endl; 
                }
                else
                {
                    //if node already existing clean up, shouldnt happen..
                    delete node;
                }     
            }
        }
        std::cout << "(info) Generated nodes, map sizes: " << size_x << "," << size_y << std::endl;
    }

    void Map::generateMineChars()
    {
        //bomb vals
        int num_of_mines = 0;

        //make sure all nodes are created
        bool createdNodes = false;

        //loop until all mines set
        while(num_of_mines < max_num_of_mines)
        {
            for (int x = 0; x < size_x; x++)
            {
                for(int y = 0; y < size_y; y++)
                {
                    //max bombs reached?
                    if(num_of_mines < max_num_of_mines)
                    {
                        //get node
                        Node* node = nodes.getNode(x, y);
                        if(node->myChar == "X")
                        { 
                            continue;
                        }

                        //random mine chance
                        int randnum = rand() % 100;
                        if(randnum > 95)
                        {
                            node->myChar = "X";
                            std::cout << "(verbose) added a mine at Node (" << x << "," << y << ")" << std::endl; 
                            num_of_mines++;
                        }
                    }

                    //quit exit
                    if(num_of_mines >= max_num_of_mines)
                        break;   
                }

                //quit exit
                if(num_of_mines >= max_num_of_mines)
                    break;
            }
        }
        std::cout << "(info) Generated mines, num of mines: " << max_num_of_mines << std::endl;
    }

    void Map::updateAdjacentNodes()
    {
        double max_distance = 1.5;
        for (std::list<Node*>::iterator node_iter = nodes.nodes.begin(); node_iter != nodes.nodes.end(); node_iter++)
        {
            int num_of_adjacent_nodes = 0;
            for (std::list<Node*>::iterator node_iter2 = nodes.nodes.begin(); node_iter2 != nodes.nodes.end(); node_iter2++)
            {
                //skip if is same node
                if(((*node_iter)->x == (*node_iter2)->x) && ((*node_iter)->y == (*node_iter2)->y))
                {
                    continue;
                }

                //set adjacent node
                double distance = Node::getDistanceBetweenNodes((*node_iter), (*node_iter2));
                if(distance <= max_distance)
                {
                    (*node_iter)->adjacentNodes.addNode((*node_iter2));
                    num_of_adjacent_nodes++;                
                }     
            }
            std::cout << "(verbose) num of adjacent nodes for Node("<< Node::nodeCoordsAsText((*node_iter)) <<"): "<< num_of_adjacent_nodes << std::endl;    
        }

        std::cout << "(info) Update node adjacency list with max_distance: " << max_distance << std::endl;
    }

    void Map::updateNodeChars()
    {
        for (std::list<Node*>::iterator node_iter = nodes.nodes.begin(); node_iter != nodes.nodes.end(); node_iter++)
        {
            if((*node_iter)->myChar == "X")
            {
                continue;
            }

            int num_of_mines = 0;
            for (std::list<Node*>::iterator adj_iter = (*node_iter)->adjacentNodes.nodes.begin(); adj_iter != (*node_iter)->adjacentNodes.nodes.end(); adj_iter++)
            {

                if((*adj_iter)->myChar == "X")
                {
                    num_of_mines++;
                }
            }

            (*node_iter)->myChar = std::to_string(num_of_mines);
        }

         std::cout << "(info) Updated node characters " << std::endl;
    }
};