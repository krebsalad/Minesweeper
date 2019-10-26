#include "./../include/wDisplay.h"
#include "./../include/Node.h"

namespace Minesweeper
{
    LRESULT CALLBACK wDisplay::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {

        //! window procedure
        switch (message)
        {
        case WM_DESTROY:
        {
            PostQuitMessage(0);

            return 0;
        }
        break;
        }

        return DefWindowProc(hWnd, message, wParam, lParam);																	// anders default window procedure
    }

    wDisplay::wDisplay(std::string _className, std::string _windowTitle, int _width, int _height)
        :Display(_windowTitle, _width, _height),
         hInstance(GetModuleHandle(0)), nCmdShow(SW_SHOWDEFAULT), className(_className)
    {

    }
    wDisplay::~wDisplay()
    {
        UnregisterClass((className).c_str(), hInstance);
    }

    bool wDisplay::initDisplay(int _node_width, int _node_height)
    {
        node_width = _node_width;
        node_height = _node_height;

        //create window
        bool succes = createWindowOnCoords((GetSystemMetrics(SM_CXSCREEN) - width), (GetSystemMetrics(SM_CYSCREEN) - height));

        ShowWindow(hWnd, nCmdShow);																		
        UpdateWindow(hWnd);

        return succes;
    }				
    bool wDisplay::createWindowOnCoords(int x, int y)
    {
        WNDCLASSEX windowClassEx;																									

        ZeroMemory(&windowClassEx, sizeof(WNDCLASSEX));

        windowClassEx.cbSize = sizeof(windowClassEx);
        windowClassEx.style = CS_HREDRAW | CS_VREDRAW;																			
        windowClassEx.hInstance = hInstance;																						
        windowClassEx.lpfnWndProc = DefWindowProc;																						

        windowClassEx.lpszClassName = (className).c_str();																					

        windowClassEx.hbrBackground = (HBRUSH)COLOR_WINDOW;									

        windowClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);																	
        windowClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);																		
        windowClassEx.hIcon = LoadIcon(NULL, IDI_WINLOGO);																			

        if (RegisterClassEx(&windowClassEx) == false)																				
        {
            initialized = false;
            MessageBox(NULL, "Failed creating window!!", NULL, NULL);
            return false;
        }

        hWnd = CreateWindowEx(NULL, (className).c_str(), (windowName).c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, hInstance, NULL);	

        ShowWindow(hWnd, nCmdShow);																		
        UpdateWindow(hWnd);

        initialized = true;
        return true;

    }		

    bool wDisplay::run()
    {
        if (initialized == true)	//maak nieuwe window aan
	    {
            while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))					
            {

                DispatchMessage(&message);										
            }

            if (message.message == WM_QUIT)
            {
                return false;
            }
            return true;
        }
        return false;

        ShowWindow(hWnd, nCmdShow);	
    }

    HWND* wDisplay::getWindowHandle()
    {
        return &hWnd;
    }

    bool wDisplay::updateNodes(NodeList &reveleadNodes)
    {
        return true;
    }

}