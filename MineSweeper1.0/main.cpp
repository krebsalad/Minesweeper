#include "./include/uNode.h"
#include "./include/Game.h"
#include <iostream>

int main(int argc, const char** argv) {
    Minesweeper::Game g(20,20);
    g.init();
    g.run();
    
    return 0;
}

