#ifndef DISPLAYGL_H_
#define DISPLAYGL_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Display.h"

namespace Minesweeper
{
    class ObjectData
    {
        //uuid
        public:
            std::string name;

            unsigned int sequence_nr;

            float* vertices;
            unsigned int vlen;
            unsigned int vertexBuffer;

            unsigned int* indices;
            unsigned int ilen;
            unsigned int indexBuffer;

            //shaders
            std::string vShader;
            std::string fShader;
            unsigned int shader_program;
            ObjectData(unsigned int _sequence_nr, std::string _name);
            ~ObjectData();

            static unsigned int nxt_sequence_nr;
        
    };
    

    class DisplayGL : public Display
    {
        public:
            DisplayGL(int w, int h, std::string n);
            ~DisplayGL();

            bool init();
            bool update();
            void clear();
            void draw();
            
            void addStaticVertices2d(std::string name, float* vertices, unsigned int vert_len, unsigned int* indicies, unsigned int indi_len);
           
        private:
            GLFWwindow* window;
            std::list<ObjectData*> objects;

            static unsigned int createShader(const std::string& vShader, const std::string& fShader);
            static unsigned int compileShader(unsigned int type, const std::string& source);
            static std::string readShaderFromFile(std::string type, std::string filePath);
    };


};


#endif// DISPLAYGL_H_
