#include <Light.h>

LightComponent::LightComponent(GLuint _shader, Transform* _transform, int _type){
    transform = _transform;
    shader = _shader;
    type = _type;

    switch (type)
    {
        case 2: //POINTLIGHT
            glUniform1f( glGetUniformLocation( shader, GetPointLightUniform("constant")), 1.0f);
            glUniform1f( glGetUniformLocation( shader, GetPointLightUniform("linear")), 0.09f);
            glUniform1f( glGetUniformLocation( shader, GetPointLightUniform("quadratic")), 0.032f);
            break;
        
    }
};

void LightComponent::Update(){
    GLint lightPosLoc;
    GLint lightDirLoc;
    
    switch (type)
    {
        //UPDATE LIGHT DIRECTION IF IS A DIRECTIONAL LIGHT
        case 1:
            lightDirLoc = glGetUniformLocation( shader, "directionalLight.direction" );
            
            glUniform3f(lightDirLoc, transform->rotation.x, 
                                    transform->rotation.y, 
                                    transform->rotation.z);    
            
            glUniform3f(glGetUniformLocation(shader, "directionalLight.ambient"), ambient.r, ambient.g, ambient.b);
            glUniform3f(glGetUniformLocation(shader, "directionalLight.diffuse"), diffuse.r, diffuse.g, diffuse.b);
            glUniform3f(glGetUniformLocation(shader, "directionalLight.specular"), specular.r, specular.g, specular.b);
            break;
        //UPDATE LIGHT POSITION IF IS A SPOTLIGHT
        case 2:
            lightPosLoc = glGetUniformLocation( shader, GetPointLightUniform("position"));

            glUniform3f(lightPosLoc,transform->position.x, 
                                    transform->position.y, 
                                    transform->position.z);
            
            glUniform3f(glGetUniformLocation(shader, GetPointLightUniform("ambient")), ambient.r, ambient.g, ambient.b);
            glUniform3f(glGetUniformLocation(shader, GetPointLightUniform("diffuse")), diffuse.r, diffuse.g, diffuse.b);
            glUniform3f(glGetUniformLocation(shader, GetPointLightUniform("specular")), specular.r, specular.g, specular.b);
            break;

        default:
            break;
    }
}

const char* LightComponent::GetPointLightUniform(const char* _data){
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