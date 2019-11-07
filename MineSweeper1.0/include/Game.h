#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <list>

namespace Minesweeper
{
    class Display;

    class Game
    {
        public:
            Game(int sx, int sy, Display* _wnd);
            ~Game();
   
            bool init();  
            void run();

        private:
            const int size_x, size_y;
            std::list<std::string> reveleadNodes;
            Display* display;

            //init
            void generateMineChars();
            void updateNodeChars();
            void printNodes();

            //run
            bool actionOnNode(std::string target_node);
            void revealeNode(std::string target_node);
            void revealeAdjacentNodes(std::string target_node);

            //display
            void setupDisplay();
            void createDisplayNodes();
    };
};


#endif //!GAME_H_