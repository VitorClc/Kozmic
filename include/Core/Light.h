#pragma once 

#define GLEW_STATIC

#include <GL/glew.h>

#include <Component.h>
#include <Transform.h>

class LightComponent : public Component{
    public:
        LightComponent(GLuint _shader, Transform* _transform, int _type);
        void Start(){};
        void Update();

        Transform* transform;        
        GLuint shader;
        int type;
};