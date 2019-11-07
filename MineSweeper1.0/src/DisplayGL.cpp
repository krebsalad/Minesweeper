#include "./../include/DisplayGL.h"
#include <iostream>
#include <fstream>

namespace Minesweeper 
{
    unsigned int ObjectData::nxt_sequence_nr = 0;

    ObjectData::ObjectData(unsigned int _sequence_nr, std::string _name)
        : sequence_nr(_sequence_nr), name(_name)
    {
        ObjectData::nxt_sequence_nr++;
    }

    ObjectData::~ObjectData()
    {
        if(vertices != NULL)
        {
            delete vertices;
        }

        if(indices != NULL)
        {
            delete indices;
        }
    }

    std::string DisplayGL::readShaderFromFile(std::string type, std::string path)
    {
        //read file
        std::ifstream file(path);

        std::string shader = "";
       
        std::string line;
        bool foundShader = false;
        
        //read lines to find #shader
        while (std::getline(file, line))
        {
            //add lines if shader found
            if(foundShader)
            {
                //quit if found another shader
                if(line.find("#shader") != std::string::npos)
                {
                    foundShader = false;
                    break;
                }

                shader += line + "\n";
                continue;
            }

            //check if shader type is in line
            if(line.find("#shader " + type) != std::string::npos && !foundShader)
            {
                foundShader = true;
                continue;
            }  
        }
        return shader;
    }

    unsigned int DisplayGL::compileShader(unsigned int type, const std::string& source)
    {   
        //create and compile opengl shader
        unsigned int sId = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(sId, 1, &src, nullptr);
        glCompileShader(sId);

        //print error
        int succes;
        glGetShaderiv(sId, GL_COMPILE_STATUS, &succes);
        if(!succes)
        {
            std::cout << "Display: failed compiling shader" << std::endl;
            int length;
            glGetShaderiv(sId, GL_INFO_LOG_LENGTH, &length);
            char* message = new char[length];
            glGetShaderInfoLog(sId, length, &length, message);
            std::cout << message << std::endl;
            delete message;
            return 0;
        }

        return sId;
    }

    unsigned int DisplayGL::createShader(const std::string& vShader, const std::string& fShader)
    {
        //create shader program
        unsigned int pId = glCreateProgram();
        std::cout << "Display: created shader program " << std::to_string(pId) << std::endl;

        //create shaders
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fShader);

        //attach shaders to program
        glAttachShader(pId, vs);
        glAttachShader(pId, fs);
        glLinkProgram(pId);
        glValidateProgram(pId);
        
        //cleanup shaders
        glDeleteShader(vs);
        glDeleteShader(fs);
        return pId;
    }

    DisplayGL::DisplayGL(int w, int h, std::string n)
        : Display(w, h, n)
    {
    }

    DisplayGL::~DisplayGL()
    {
        //delete pointers
        for(std::list<ObjectData*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
        {
            if((*iter) != NULL)
                delete (*iter);
        }
    }

    bool DisplayGL::init()
    {
        //only init once
        if(!initialized)
        {
            std::cout << "Display: creating window " << name << std::endl;

            //window init
            if (!glfwInit())
            {
                std::cout << "Display: failed initializing glfw" << std::endl;
                return false;
            }

            //create window and opengl context
            window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                std::cout << "Display: failed creating window " << name << std::endl;
                return false;
            }

            glfwMakeContextCurrent(window);

            //init glew for modern opengl
            if(glewInit() != GLEW_OK)
            {
                std::cout << "Display: failed initializing glew" << std::endl;
                return false;
            }


            std::cout << "Display: succesfully created window " << name << " opengl " << glGetString(GL_VERSION)  << std::endl;
            initialized = true;
            
        }
        return true;
    }

    void DisplayGL::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void DisplayGL::addStaticVertices2d(std::string name, float* vertices, unsigned int vert_len, unsigned int* indices, unsigned int indi_len)
    {
        //create and bind buffer
        unsigned int vertexBuffer;
        unsigned int sequence_nr;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vert_len * sizeof(float), vertices, GL_STATIC_DRAW);

        //set vertex attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        //create and bind indexbuffer
        unsigned int indexBuffer;
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indi_len * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        // read shaders
        std::string vShader = readShaderFromFile("vertex", "./assets/shaders/map.shader");
        //std::cout << "Display: read vshader: \n" << vShader << std::endl;
        std::string fShader = readShaderFromFile("fragment", "./assets/shaders/map.shader");
        //std::cout << "Display: read fshader: \n" << fShader << std::endl;

        //create and use shader program
        unsigned int shader = createShader(vShader, fShader);
        glUseProgram(shader);

        //save pointers
        ObjectData* objData = new ObjectData(sequence_nr, name);

        objData->vertices = vertices;
        objData->vlen = vert_len;
        objData->vertexBuffer = vertexBuffer;

        objData->indices = indices;
        objData->ilen = indi_len;
        objData->indexBuffer = indexBuffer;

        objData->vShader = vShader;
        objData->fShader = fShader;
        objData->shader_program = shader;

        objects.push_back(objData);
    }

    void DisplayGL::draw()
    {
        for(std::list<ObjectData*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
        {
            glDrawElements(GL_TRIANGLES, (*iter)->ilen, GL_UNSIGNED_INT, nullptr);
        }
    }

    bool DisplayGL::update(void)
    {
        //update window
        if (!glfwWindowShouldClose(window))
        {
            glfwSwapBuffers(window);
            glfwPollEvents();
            return true;      
        }
 
        //delete gl object data before terminating
        for(std::list<ObjectData*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
        {
           glDeleteProgram((*iter)->shader_program);
           glDeleteBuffers(1, &((*iter)->vertexBuffer));
           glDeleteBuffers(1, &((*iter)->indexBuffer));
           std::cout << "Display: deleted "<< (*iter)->name << " shader program and buffers" << std::endl;
        }

        //stop window
        glfwTerminate();
        std::cout << "Display: exited window" << std::endl;
        return false;
    }

}