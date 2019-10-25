#include "./../include/Game.h"
#include "./../include/Node.h"
#include <iostream>

namespace Minesweeper
{

    Game::Game()
        : map(10, 10)
    {
        std::cout << "(game) Starting mine sweeper game";
        map.initNodes();
    }

    Game::~Game()
    {

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

        while(actionOnNode(input_val1,input_val2))
        {
            map.printNodes(revealedNodes);

            //check if done
            if(revealedNodes.nodeCount() == (map.nodes.nodeCount() - map.max_num_of_mines))
            {
                std::cout << "(event) found all mines";
                std::cout << "(game) Game won!!";
                return;
            }

            //ask for node to click
            std::cout << "(action) Type a value x of to open box: ";
            std::cin >> input_val1;
            std::cout << "\n(action) Type a value y of to open box: ";
            std::cin >> input_val2;
            std::cout << "\n";         
        } 

        std::cout << "(game) Game lost!";
        return;
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
        map.nodes.unmarkNodes();

        //get target node
        std::cout << "(event) Open Node action on Node (" << x << "," << y << ")" << std::endl;
        Node* target_node = map.nodes.getNode(x, y);

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