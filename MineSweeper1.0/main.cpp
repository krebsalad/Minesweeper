#include "./include/uNode.h"
#include "./include/Game.h"
#include <iostream>

int main(int argc, const char** argv) {

    //uNode::createNodes2d(10, 10);
    //uNode node = uNode::getNode2d(5,5);
    //std::cout << "adjacency list for node " << node.nodeId << std::endl;
    

    Minesweeper::Game g(20,20);
    g.init();
    g.run();
    
    return 0;
}

