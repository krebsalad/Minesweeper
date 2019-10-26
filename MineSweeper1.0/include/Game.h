#ifndef  GAME_H_
#define GAME_H_

#include "NodeList.h"

namespace Minesweeper
{
    class Map;
    class Display;

    class Game 
    {
        public:
            Map* map;
            std::list<Display*> displays;
            NodeList revealedNodes;

        public:
            Game();
            ~Game();
            bool run();
            bool run(bool console_mode);
            bool init(int width, int heigth);
            bool actionOnNode(int x, int y);
            void updateDisplays();
            void showDisplays();
            void addDisplay(Display* _display);

        private:
            void revealeNode(Node* node);
            void revealeAdjacentNodes(Node* node);
    };
}

#endif // ! GAME_H_