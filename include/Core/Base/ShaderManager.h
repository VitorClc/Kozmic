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
        
        std::vector<Shader*> shaders;
    
    private:
        ShaderManager(){};

};