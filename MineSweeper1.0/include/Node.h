#ifndef  NODE_H_
#define NODE_H_

#include <string>
#include "./NodeList.h"

namespace Minesweeper
{
    class Node {
            public:        
                const int x;
                const int y;
                std::string myChar;
                NodeList adjacentNodes;

                bool marked;

            public:
                Node(int _x, int _y);
                ~Node();

                static std::string nodeCoordsAsText(Node* node);
                static std::string coordsAsText(int x, int y);
                static double getDistanceBetweenNodes(Node* node1, Node* node2);
    };
};

#endif // ! NODE_H_