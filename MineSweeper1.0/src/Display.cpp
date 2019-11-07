#include "./../include/Display.h"

namespace Minesweeper
{
    Display::Display(int w, int h, std::string n)
        : width(w), height(h), name(n)
    {
        
    }

    bool Display::isInitalized()
    {
        return initialized;
    }
    
}
