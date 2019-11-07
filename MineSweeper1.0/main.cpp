#include "./include/uNode.h"
#include "./include/Game.h"
#include "./include/DisplayGL.h"
#include <iostream>

int main(int argc, const char** argv) {
    //create game object
    Minesweeper::Game g(9,9,new Minesweeper::DisplayGL(1280, 720, "Minesweeper window"));

    //init window and nodes
    if(!g.init())
    {
        return 0;
    }

    //run the game
    g.run();
    
    std::cout << "exiting game" << std::endl;
    return 0;
}



