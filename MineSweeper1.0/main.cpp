
#include <iostream>
#include <list>
#include <string>

#include "./include/wDisplay.h"
#include "./include/cDisplay.h"
#include "./include/Game.h"

int main()
{
    //create window and game
    Minesweeper::Game game;

    //create windows
    Minesweeper::Display* wnd = new Minesweeper::wDisplay("minesweeper_window", "window", 1280, 720);
    Minesweeper::Display* debug_wnd = new Minesweeper::cDisplay("console_window");

    //add displays
    game.addDisplay(wnd);
    game.addDisplay(debug_wnd);

    //init
    if(!game.init(10, 10))
    {
        delete wnd;
        return 0;
    }

    //run game
    if(!game.run())
    {
        std::cout << "game exited with an error" << std::endl;
    }

    std::cout << "exiting..." << std::endl;
    return 0;
}