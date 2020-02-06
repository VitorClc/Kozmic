#pragma once

#define GLEW_STATIC

#include <Base/Component.h>

#include <gtx/transform.hpp>

#include <GL/glew.h>

#include <iostream>

class Transform : public Component
{
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::vec3 worldUp = glm::vec3(0.0, 1.0, 0.0);
        glm::vec3 front = glm::vec3(0.0, 0.0, -1.0);
        glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
        glm::vec3 right = glm::vec3(1.0, 0.0, 0.0 );
        
        Transform(
            glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f)
        );

        glm::mat4 GetMatrix();
        void SetMatrix(glm::mat4 _matrix);

        Transform* GetParent();
        void SetParent(Transform* _parent);
        bool HasParent();

    private:
        glm::mat4 transform;

        Transform* parent;

        void Start(){};
        void Update(){};

};