#pragma once

#include <gtc/type_ptr.hpp>

#include <GameObject.h>
#include <Transform.h>

class Camera : public Component
{
    public:
        Camera(std::vector<GLuint> _shaders, Transform* _transform);

        void Start();

        void Update();
        
        std::vector<GLuint> shaders;

    private:

        Transform* transform;

        glm::mat4 projection;
};
