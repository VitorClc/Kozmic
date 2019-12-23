#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>

//TODO: EXTERNAL SHADER LOAD
class Shader
{
    public:
        void LoadBasic();

        GLuint GetID();

    private:
        GLuint shaderID;     
};

