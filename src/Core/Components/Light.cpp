#include <Components/Light.h>

LightComponent::LightComponent(Transform* _transform, int _type){
    transform = _transform;
    type = _type;

    shaderID = shaderManager.GetShader(0);

    switch (type)
    {
        case 2: //POINTLIGHT
            glUniform1f( glGetUniformLocation( shaderID, GetPointLightUniform("constant").c_str()), 1.0f);
            glUniform1f( glGetUniformLocation( shaderID, GetPointLightUniform("linear").c_str()), 0.09f);
            glUniform1f( glGetUniformLocation( shaderID, GetPointLightUniform("quadratic").c_str()), 0.032f);
            break;
        
    }
};

void LightComponent::Update(){    
    switch (type)
    {
        //UPDATE LIGHT DIRECTION IF IS A DIRECTIONAL LIGHT
        case 1:
            lightDirLoc = glGetUniformLocation( shaderID, "directionalLight.direction" );
            
            glUniform3f(lightDirLoc, transform->rotation.x, 
                                    transform->rotation.y, 
                                    transform->rotation.z);    
            
            glUniform3f(glGetUniformLocation(shaderID, "directionalLight.ambient"), ambient.r, ambient.g, ambient.b);
            glUniform3f(glGetUniformLocation(shaderID, "directionalLight.diffuse"), diffuse.r, diffuse.g, diffuse.b);
            glUniform3f(glGetUniformLocation(shaderID, "directionalLight.specular"), specular.r, specular.g, specular.b);
            break;
        //UPDATE LIGHT POSITION IF IS A SPOTLIGHT
        case 2:
            lightPosLoc = glGetUniformLocation( shaderID, GetPointLightUniform("position").c_str());
            
            glUniform3f(lightPosLoc,transform->position.x, 
                                    transform->position.y, 
                                    transform->position.z);
            
            glUniform3f(glGetUniformLocation(shaderID, GetPointLightUniform("ambient").c_str()), ambient.r, ambient.g, ambient.b);
            glUniform3f(glGetUniformLocation(shaderID, GetPointLightUniform("diffuse").c_str()), diffuse.r, diffuse.g, diffuse.b);
            glUniform3f(glGetUniformLocation(shaderID, GetPointLightUniform("specular").c_str()), specular.r, specular.g, specular.b);
            
            break;

        default:
            break;
    }
}

std::string LightComponent::GetPointLightUniform(const char* _data){
    std::string lightID = "pointLightSources[";
    lightID += std::to_string(id);
    lightID += "]";
    
    std::string lightData = ".";
    lightData += _data;

    std::string completeAccess;
    completeAccess += lightID.c_str();
    completeAccess += lightData.c_str();

    return completeAccess;
}