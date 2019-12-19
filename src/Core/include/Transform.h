#define GLEW_STATIC

#include <glm.hpp>
#include <gtx/transform.hpp>

#include <GL/glew.h>

class Transform
{
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Transform(
            glm::vec3 _position = glm::vec3(0.0, 0.0f, 0.0f), 
            glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f)
        )
        {
            position = _position;
            rotation = _rotation;
            scale = _scale;

            transform = glm::mat4(1.0f);
        }

        glm::mat4 getMatrix(){
            glm::mat4 positionMatrix = glm::translate(position);
            glm::mat4 rotationXMatrix = glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 rotationYMatrix = glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 rotationZMatrix = glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 scaleMatrix = glm::scale(scale);
            return positionMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * scaleMatrix;
        }

    private:
        glm::mat4 transform;
};