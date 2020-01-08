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
            lightPosLoc = glGetUniformLocation( shader, GetLightUniform("position"));

            glUniform3f(lightPosLoc,transform->position.x, 
                                    transform->position.y, 
                                    transform->position.z);
            break;

        case 2:
            //lightDirLoc = glGetUniformLocation( shader, "pointLightSource.direction" );
            
            //glUniform3f(lightDirLoc,transform->rotation.x, 
            //                        transform->rotation.y, 
            //                        transform->rotation.z);    
            break;

        default:
            break;
    }

    glUniform3f(glGetUniformLocation(shader, GetLightUniform("ambient")), ambient.r, ambient.g, ambient.b);
    glUniform3f(glGetUniformLocation(shader, GetLightUniform("diffuse")), diffuse.r, diffuse.g, diffuse.b);
    glUniform3f(glGetUniformLocation(shader, GetLightUniform("specular")), specular.r, specular.g, specular.b);
}

const char* LightComponent::GetLightUniform(const char* _data){
    std::string lightID = "pointLightSources[";
    lightID += std::to_string(id);
    lightID += "]";
    
    std::string lightData = ".";
    lightData += _data;

    std::string completeAccess;
    completeAccess += lightID.c_str();
    completeAccess += lightData.c_str();

    return completeAccess.c_str();
}