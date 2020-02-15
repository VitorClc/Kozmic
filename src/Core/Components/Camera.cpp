#include <Components/Camera.h>

Camera::Camera(Transform* _transform){
    transform = _transform;
}

void Camera::Start(){
    projection = glm::perspective(45.0f, 1024.0f / 720.0f, 0.1f, 1000.0f);            
}

void Camera::Update(){
    glm::vec3 viewFront;
    viewFront.x = cos(glm::radians(transform->rotation.y)) * cos(glm::radians(transform->rotation.x));
    viewFront.y = sin(glm::radians(transform->rotation.x));
    viewFront.z = sin(glm::radians(transform->rotation.y)) * cos(glm::radians(transform->rotation.x));
    
    transform->front = glm::normalize(viewFront);

    transform->right = glm::normalize(glm::cross(transform->front, transform->worldUp));
    transform->up    = glm::normalize(glm::cross(transform->right, transform->front));

    glm::mat4 view = glm::lookAt(transform->position, transform->position + transform->front, transform->up);
    
    for(unsigned int i = 0; i < shaderManager.ShaderAmount(); i++){
        unsigned int viewLoc = glGetUniformLocation(shaderManager.GetShader(i), "view");
        unsigned int projectionLoc = glGetUniformLocation(shaderManager.GetShader(i), "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }
}
