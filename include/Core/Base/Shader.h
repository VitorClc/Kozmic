#pragma once
#define GLEW_STATIC

#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>

class Shader
{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);

        GLuint GetID();

    private:
        void Load(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
        GLuint shaderID;     
};

