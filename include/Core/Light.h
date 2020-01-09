#pragma once 

#define GLEW_STATIC

#include <GL/glew.h>

#include <Component.h>
#include <Transform.h>

class LightComponent : public Component{
    public:
        LightComponent(GLuint _shader, Transform* _transform, int _type);
        const char* GetPointLightUniform(const char* _data);

        glm::vec3 ambient = glm::vec3(0.3f, 0.3f, 0.3f);
        glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

        void Update();
    
        Transform* transform;        
        GLuint shader;
        int type;
        int id;
    
    private:
        void Start(){};
};