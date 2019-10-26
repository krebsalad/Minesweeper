#include "./../include/Display.h"

namespace Minesweeper
{
    Display::Display(std::string _windowName, int _width, int _height)
        :windowName(_windowName), width(_width), height(_height), initialized(false)
    {
        
    }

    Display::~Display()
    {

    }

    bool Display::isInitialized()
    {
        return initialized;
    }
}