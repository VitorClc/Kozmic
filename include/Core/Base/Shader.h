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
        void Compile();

        std::string vertexShaderSource;
        std::string fragmentShaderSource;

        GLuint GetID();

    private:
        GLuint shaderID;     
};

