#ifndef  DISPLAY_H_
#define DISPLAY_H_

#include <string>
#include "./NodeList.h"

namespace Minesweeper
{
    class Display
    {
        public:
            
            virtual ~Display();

            virtual bool initDisplay(int _node_width, int _node_height) = 0;    
            virtual bool run() = 0;
            virtual bool updateNodes(NodeList &nodes, NodeList &reveleadNodes) = 0;
            bool isInitialized();

            //window vars
            std::string windowName;

        protected:
            Display(std::string _windowName, int _width, int _height);

            //window vars
            int width;
            int height;
            bool initialized;
            
            //game vars
            int node_width;
            int node_height;
    };

};

#endif //