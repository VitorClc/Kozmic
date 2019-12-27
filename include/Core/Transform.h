#pragma once

#define GLEW_STATIC

#include <Component.h>

#include <gtx/transform.hpp>

#include <GL/glew.h>

class Transform : public Component
{
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Transform(
            glm::vec3 _position = glm::vec3(0.0, 0.0f, 0.0f), 
            glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f)
        );

        glm::mat4 GetMatrix();
        void SetMatrix(glm::mat4 _matrix);

        void SetParent(Transform* _parent);

    private:
        glm::mat4 transform;

        Transform* parent;
        glm::mat4 parentTransform;

        void Start(){};
        void Update(){};

};