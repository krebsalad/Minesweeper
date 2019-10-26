
#ifndef WDISPLAY_H_
#define WDISPLAY_H_

#include "./Display.h"
#include <windows.h>
#include <string>

namespace Minesweeper
{
    class wDisplay : public Display
    {
        public:
            wDisplay(std::string _className, std::string _windowTitle, int _width, int _height); //! create with className, windowtitle and window sizes
            ~wDisplay();

            bool initDisplay(int _node_width_x, int _node_width_y);			
            bool run();
            bool updateNodes(NodeList &nodes, NodeList &reveleadNodes);

            LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	
            HWND* getWindowHandle();



        private:
            bool createWindowOnCoords(int x, int y);

            HWND hWnd;
            MSG message;
            HINSTANCE hInstance;
            int nCmdShow;
            std::string className;
        };
};

#endif //

