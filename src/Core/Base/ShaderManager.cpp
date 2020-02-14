#include <Base/ShaderManager.h>
#include <Base/test.h>

void ShaderManager::AddShader(Shader* _shader){
    shaders.push_back(_shader);
}

void ShaderManager::CompileShaders(){
    for(int i = 0; i < shaders.size(); i++){
        shaders[i]->Compile();
    }
}