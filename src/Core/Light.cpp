#include <Light.h>

LightComponent::LightComponent(GLuint _shader, Transform* _transform, int _type){
    transform = _transform;
    shader = _shader;
    type = _type;

    switch (type)
    {
        case 1: //POINTLIGHT
            glUniform1f( glGetUniformLocation( shader, "lightSource.constant"), 1.0f);
            glUniform1f( glGetUniformLocation( shader, "lightSource.linear"), 0.09f);
            glUniform1f( glGetUniformLocation( shader, "lightSource.quadratic"), 0.032f);
            break;
        
        default:
            break;
    }
};

void LightComponent::Update(){
    GLint lightPosLoc;
    GLint lightDirLoc;

    //UPDATE LIGHT POSITION IF IS A SPOTLIGHT
    switch (type)
    {
        case 1:
            lightPosLoc = glGetUniformLocation( shader, "lightSource.position" );
            
            glUniform3f(lightPosLoc,transform->position.x, 
                                    transform->position.y, 
                                    transform->position.z);
            break;

        case 2:
            lightDirLoc = glGetUniformLocation( shader, "lightSource.direction" );
            
            glUniform3f(lightDirLoc,transform->rotation.x, 
                                    transform->rotation.y, 
                                    transform->rotation.z);    
            break;

        default:
            break;
    }

    glUniform3f(glGetUniformLocation(shader, "lightSource.ambient"), 0.3f,0.3f,0.3f);
    glUniform3f(glGetUniformLocation(shader, "lightSource.diffuse"), 0.5f,0.5f,0.5f);
    glUniform3f(glGetUniformLocation(shader, "lightSource.specular"), 1.0f,1.0f,1.0f);
}