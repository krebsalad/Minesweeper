#ifndef  GAME_H_
#define GAME_H_

#include "./Map.h"

namespace Minesweeper
{
    class Node;

    class Game 
    {
        public:
            Map map;
            NodeList revealedNodes;

        public:
            Game();
            ~Game();
            void run();
            bool actionOnNode(int x, int y);

        private:
            void revealeNode(Node* node);
            void revealeAdjacentNodes(Node* node);
    };
}

#endif // ! GAME_H_