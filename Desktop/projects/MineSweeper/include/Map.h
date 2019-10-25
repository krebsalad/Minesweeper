#ifndef MAP_H_
#define MAP_H_

#include "./NodeList.h"

namespace Minesweeper
{
    class Map {
        public:
            const int size_x;
            const int size_y;
            const int max_num_of_mines;

        public:
            Map(int _sx, int _sy);

            ~Map();     

            void initNodes();
            void printNodes(NodeList &reveleadNodes);
            NodeList nodes;

        private:
            void generateNodes(); 
            void updateAdjacentNodes();
            void generateMineChars();
            void updateNodeChars();

            
    };
};

#endif // !MAP_H_