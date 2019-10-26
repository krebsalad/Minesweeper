#include "./../include/Node.h"
#include <math.h>

namespace Minesweeper
{
    Node::Node(int _x, int _y)
            : x(_x), y(_y), myChar(" "), marked(false)
    {

    };

    Node::~Node()
    {

    }

    std::string Node::nodeCoordsAsText(Node* node)
    {
        return std::to_string(node->x) + "," + std::to_string(node->y);
    }

    std::string Node::coordsAsText(int x, int y)
    {
        return std::to_string(x) + "," + std::to_string(y);
    }


    double Node::getDistanceBetweenNodes(Node* node1, Node* node2)
    {
        double dis_x = abs((double)(node1->x) - (double)(node2->x));
        double dis_y = abs((double)(node1->y) - (double)(node2->y));
        double dis = sqrt(pow(dis_x, 2.0) + pow(dis_y, 2.0));
        return dis;
    };
};