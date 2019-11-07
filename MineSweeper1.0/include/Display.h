#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>
#include <list>

namespace Minesweeper
{
    class Display
    {
        public:
            Display(int w, int h, std::string n);
            virtual ~Display() = default;

            virtual bool init() = 0;
            virtual bool update() = 0;
            virtual void clear() = 0;
            virtual void draw() = 0;

            virtual void addStaticVertices2d(std::string name, float* vertices, unsigned int vert_len, unsigned int* indicies, unsigned int indi_len) = 0;
            bool isInitalized();
           
        protected:
            bool initialized;
            int width;
            int height;
            std::string name;

    };


};


#endif// DISPLAY_H_
