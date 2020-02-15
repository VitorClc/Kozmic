#pragma once 

#define GLEW_STATIC

#include <GL/glew.h>

#include <Base/Component.h>
#include <Base/ShaderManager.h>

#include <Components/Transform.h>

class LightComponent : public Component{
    public:
        LightComponent(Transform* _transform, int _type);
        std::string GetPointLightUniform(const char* _data);

        glm::vec3 ambient = glm::vec3(0.3f, 0.3f, 0.3f);
        glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

        void Update();
    
        Transform* transform;        
        int type;
        int id;
        GLuint shaderID;

    private:
        void Start(){};
        GLint lightPosLoc;
        GLint lightDirLoc;

        ShaderManager& shaderManager = ShaderManager::getInstance();
};