#include "./../include/NodeList.h"
#include "./../include/Node.h"
#include <iostream>

namespace Minesweeper
{
    NodeList::NodeList()
        : nodes(std::list<Node*>())
    {
        
    }

    NodeList::~NodeList()
    {
    };

    void NodeList::clear(bool remove)
    {
        if(remove == true)
        {
            for (std::list<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
            {
                delete (*iter);
            }
        }
        nodes.clear();
    }

    bool NodeList::addNode(Node* node)
    {
        if(node == NULL)
        {
            std::cout << "(fail) did not add node: was null" << std::endl;
            return false;
        }

        if(getNode(node->x, node->y) != NULL)
        {
            std::cout << "(fail) did not add Node(" << node->nodeCoordsAsText() << "): already existing" << std::endl;
            return false;
        }

        nodes.push_back(node);
        return true;
    }

    Node* NodeList::getNode(int x, int y)
    {
        for (std::list<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
        {
            if((*iter)->x == x && (*iter)->y == y)
            {
                return (*iter);
            }
        }

        return NULL;
    }

    bool NodeList::removeNode(int x, int y)
    {
        for (std::list<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
        {
            if((*iter)->x == x && (*iter)->y == y)
            {
                nodes.remove(*iter);
                return true;
            }
        }

        std::cout << "(fail) did not remove node: was null" << std::endl;
        return false;
    }

    void NodeList::unmarkNodes()
    {
        for (std::list<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
        {
            (*iter)->marked = false;
        }
    }

    int NodeList::nodeCount()
    {
        return nodes.size();
    }
};