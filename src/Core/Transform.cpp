#include <Transform.h>

Transform::Transform(
    glm::vec3 _position, 
    glm::vec3 _rotation, 
    glm::vec3 _scale
)
{
    position = _position;
    rotation = _rotation;
    scale = _scale;

    transform = glm::mat4(1.0f);
}

glm::mat4 Transform::GetMatrix(){
    glm::mat4 positionMatrix = glm::translate(position);
    glm::mat4 rotationXMatrix = glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationYMatrix = glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZMatrix = glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaleMatrix = glm::scale(scale);
    
    if(parent != NULL){
        parentTransform = glm::mat4(1.0f);
        parentTransform = parent->GetMatrix();
        return parentTransform * positionMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * scaleMatrix;
    }
    else{
        return positionMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * scaleMatrix;
    }
}

void Transform::SetMatrix(glm::mat4x4 _matrix){
    transform = _matrix;
}

void Transform::SetParent(Transform* _parent){
    parent = _parent;
}