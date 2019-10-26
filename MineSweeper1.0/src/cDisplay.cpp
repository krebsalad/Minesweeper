#include "./../include/cDisplay.h"
#include "./../include/Node.h"
#include <iostream>

namespace Minesweeper {
    cDisplay::cDisplay(std::string _windowName) : Display(_windowName, 0, 0)
    {

    }
    cDisplay::~cDisplay()
    {

    }

    bool cDisplay::initDisplay(int _node_width, int _node_height)
    {
        node_width = _node_width;
        node_height = _node_height;
        initialized = true;
        return true;
    }   

    bool cDisplay::run()
    {
        //print line
        std::cout << "\n(game) Nodes: \n" << frame.c_str();
        return true;
    }

    bool cDisplay::updateNodes(NodeList &reveleadNodes)
    {
        //clear frame
        frame = "";

        //create ascii image
        for (int x = 0; x < node_width; x++)
        {
            //(7 * size_y) + 1 ascci character to draw line end with newline
            for(int y =0; y < node_height; y++)
            {
                frame += "+------";
            }
            frame += "+\n";

            //3 * new line ascci character 
            for(int line = 0; line < 3; line++)
            {
                //(7 * size_y) + 1 ascci character to draw line end with newline
                for(int y = 0; y < node_height; y++)
                {
                    //get node to draw
                    if(line == 0)
                    {
                        //print coords
                        std::string ntxt = Node::coordsAsText(x, y);
                        frame += "|"+ntxt;

                        //ensure the added text is expected length
                        for(int t = 0; t < (6-ntxt.length()); t++)
                            frame += " ";

                        continue;
                    }
                    
                    //check if revelealed
                    if(line == 1)
                    {
                        Node* node = reveleadNodes.getNode(x,y);
                        //print character
                        if(node != NULL)
                        {
                            frame += "|   " + node->myChar + "  ";
                            continue;
                        }

                    }

                    //check if revelealed
                    if(line == 2)
                    {
                        //print character
                        Node* node = reveleadNodes.getNode(x,y);
                        if(node != NULL)
                        {
                            frame += "|   ^  ";
                            continue;
                        }
                    }
                    //default
                    frame += "|      ";
                }
                frame += "|\n";
            }   
        }

        // draw last line
        for(int y =0; y < node_height; y++)
        {
            frame += "+------";
        }
        frame += "+\n";
    }
}