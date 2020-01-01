#include <Camera.h>

Camera::Camera(GLuint _shader, Transform* _transform){
    shader = _shader;
    transform = _transform;
}

void Camera::Start(){
    projection = glm::perspective(45.0f, 1024.0f / 720.0f, 0.1f, 1000.0f);            
}

void Camera::Update(){
    unsigned int viewLoc = glGetUniformLocation(shader, "view");
    unsigned int projectionLoc = glGetUniformLocation(shader, "projection");
    
    glm::vec3 viewFront;
    viewFront.x = cos(glm::radians(transform->rotation.y)) * cos(glm::radians(transform->rotation.x));
    viewFront.y = sin(glm::radians(transform->rotation.x));
    viewFront.z = sin(glm::radians(transform->rotation.y)) * cos(glm::radians(transform->rotation.x));
    
    transform->front = glm::normalize(viewFront);

    transform->right = glm::normalize(glm::cross(transform->front, transform->worldUp));
    transform->up    = glm::normalize(glm::cross(transform->right, transform->front));

    glm::mat4 view = glm::lookAt(transform->position, transform->position + transform->front, transform->up);
    
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
