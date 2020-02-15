#pragma once

#include <Base/Shader.h>
#include <vector>

class ShaderManager{
    public:
        static ShaderManager& getInstance()
        {
            static ShaderManager INSTANCE;
            return INSTANCE;
        }

        void AddShader(Shader* _shader);
        void CompileShaders();
        
        GLuint GetShader(GLuint shaderID);
        GLuint ShaderAmount();

    private:
        ShaderManager(){};
        std::vector<Shader*> shaders;
};