#pragma once

#include <gtc/type_ptr.hpp>

#include <Base/GameObject.h>
#include <Components/Transform.h>

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
