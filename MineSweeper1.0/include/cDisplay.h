#ifndef  CDISPLAY_H_
#define CDISPLAY_H_

#include "./Display.h"

namespace Minesweeper
{
    class cDisplay : public Display
    {
        public:
            cDisplay(std::string _windowName);
            ~cDisplay();

            bool initDisplay(int _node_width, int _node_height);    
            bool run();
            bool updateNodes(NodeList &nodes, NodeList &reveleadNodes);

        private:
            std::string frame;
    };

};

#endif //