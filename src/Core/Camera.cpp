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
    
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(transform->GetMatrix()));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
