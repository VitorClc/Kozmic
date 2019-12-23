#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <GameObject.h>
#include <Transform.h>

class Camera : public Component
{
    public:
        Camera(GLuint _shader, Transform* _transform){
            shader = _shader;
            transform = _transform;
        }

        void Start(){
            projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);            
        }

        void Update(){
            unsigned int viewLoc = glGetUniformLocation(shader, "view");
            unsigned int projectionLoc = glGetUniformLocation(shader, "projection");
            
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(transform->getMatrix()));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        }

    private:
        GLuint shader;
        Transform* transform;

        glm::mat4 projection;
};
