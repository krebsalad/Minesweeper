#ifndef NODELIST_H_
#define NODELIST_H_

#include <list>

namespace Minesweeper
{
    class Node;

    class NodeList
    {
        public:

            std::list<Node*> nodes;

            NodeList();

            ~NodeList();

            void clear(bool remove);

            bool addNode(Node* node);

            Node* getNode(int x, int y);

            bool removeNode(int x, int y);

            int nodeCount();

            void unmarkNodes();
    };

};

#endif // !NODELIST_H_