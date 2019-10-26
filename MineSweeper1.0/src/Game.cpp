#include "./../include/Game.h"
#include "./../include/Node.h"
#include "./../include/Display.h"
#include "./../include/Map.h"

#include <iostream>

namespace Minesweeper
{

    Game::Game()
    {
        
    }

    Game::~Game()
    {
        delete map;
    }

    void Game::addDisplay(Display* _display)
    {
        displays.push_back(_display);
    }

    bool Game::init(int _width, int _height)
    {
        //setup minesweeper
        std::cout << "(game) Starting mine sweeper game";
        map = new Map(_width, _height);
        map->initNodes();
        
        //setup windows
        bool succes = true;
        for (std::list<Display*>::iterator display_iter = displays.begin(); display_iter != displays.end(); display_iter++)
        {
            if(!(*display_iter)->initDisplay(_width, _height))
            {
                succes = false;
                std::cout << "(game) created window: " << (*display_iter)->windowName << std::endl;
            }
        }

        return succes;
    }

    bool Game::run()
    {
        return run(true);
    }

    bool Game::run(bool console_mode)
    {
        //input values
        int input_val1;
        int input_val2;

        while(true)
        {
            //get input
            if(console_mode)
            {
                std::cout << "(action) Type a value x of to open box: ";
                std::cin >> input_val1;
                std::cout << "\n(action) Type a value y of to open box: ";
                std::cin >> input_val2;
                std::cout << "\n";  
            }

            //update action in map
            actionOnNode(input_val1,input_val2);

            //update
            updateDisplays();

            //show
            showDisplays();

            //check if done
            if(revealedNodes.nodeCount() == (map->nodes.nodeCount() - map->max_num_of_mines))
            {
                std::cout << "(event) found all mines" << std::endl;
                std::cout << "(game) Game won!!" << std::endl;
                return true;;
            }       
        } 

        std::cout << "(game) Game lost!";
        return true;
    }

    void Game::updateDisplays()
    {
        for (std::list<Display*>::iterator display_iter = displays.begin(); display_iter != displays.end(); display_iter++)
        {
            if(!(*display_iter)->isInitialized())
            {
                std::cout << "(fail) window " << (*display_iter)->windowName << " is not initalized" << std::endl;
                continue;
            }

            if(!(*display_iter)->updateNodes(map->nodes, revealedNodes))
            {
                std::cout << "(fail) something went wrong when updating window "<< (*display_iter)->windowName <<" with new changes";
            }
        }
    }

    void Game::showDisplays()
    {
        for (std::list<Display*>::iterator display_iter = displays.begin(); display_iter != displays.end(); display_iter++)
        {
            if(!(*display_iter)->isInitialized())
            {
                std::cout << "(fail) window " << (*display_iter)->windowName << " is not initalized";
                continue;
            }

            if(!(*display_iter)->run())
            {
                std::cout << "(fail)  something went wrong when running the window" <<(*display_iter)->windowName << std::endl;
            }
        }
    }

    void Game::revealeNode(Node* node)
    {
        // reveale and mark node
        if(!node->marked)
        {
            //reveale node
            revealedNodes.addNode(node);
            node->marked = true;
            
            // reavele adjacent nodes if possible
            revealeAdjacentNodes(node);
        }
    }

    void Game::revealeAdjacentNodes(Node* node)
    {
        //loop through adjacent nodes
        for (std::list<Node*>::iterator adj_node = node->adjacentNodes.nodes.begin(); adj_node != node->adjacentNodes.nodes.end(); adj_node++)
        {
           if(node->myChar == "0")
           {
               revealeNode((*adj_node));
           }
        }
    }

    bool Game::actionOnNode(int x, int y)
    {
        //setup nodes
        map->nodes.unmarkNodes();

        //get target node
        std::cout << "(event) Open Node action on Node (" << x << "," << y << ")" << std::endl;
        Node* target_node = map->nodes.getNode(x, y);

        //quit if already reaveled
        if(revealedNodes.getNode(x, y) != NULL)
        {
            std::cout << "(event) node already revelead" << std::endl;
            return true;
        }

        //reveale node
        revealeNode(target_node);

        //quit if mine
        if(target_node->myChar == "X")
        {
            std::cout << "(event) node revelead mine" << std::endl;
            return false;
        }

        return true;
    }
};