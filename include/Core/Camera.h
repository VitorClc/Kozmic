#pragma once

#include <gtc/type_ptr.hpp>

#include <GameObject.h>
#include <Transform.h>

class Camera : public Component
{
    public:
        Camera(GLuint _shader, Transform* _transform);

        void Start();

        void Update();

    private:
        GLuint shader;

        Transform* transform;

        glm::mat4 projection;
};
