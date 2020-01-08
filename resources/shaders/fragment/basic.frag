#version 330 core
struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseTexture;
    int hasDiffuseTexture;
    sampler2D specularTexture;
    int hasSpecularTexture;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

out vec4 color;

in vec3 fragPos;
in vec3 Normal;
in vec2 texCoord;

uniform vec3 viewPos;
uniform Material material;
uniform PointLight lightSource;

vec3 CalculateDirectionalLight(DirectionalLight _lightSource, vec3 _normal, vec3 _viewDirection){
    vec3 lightDirection = normalize(-_lightSource.direction);

    //DIFFUSE CALCULATION
    float diffuseCalc = max(dot(_normal, lightDirection), 0.0);

    //SPECULAR CALCULATION
    vec3 reflectDiretion = reflect(-lightDirection, _normal);
    float specularCalc = pow(max(dot(_viewDirection, reflectDiretion), 0.0), material.shininess);

    //CREATE VARIABLES TO STORE RESULTS OF PHONG SHADER
    vec3 ambientResult;
    vec3 diffuseResult;
    vec3 specularResult;

    //CHECK IF THE MATERIAL HAS A DIFFUSE TEXTURE OR JUST A DIFFUSE COLOR
    if(material.hasDiffuseTexture == 1){
        ambientResult = _lightSource.ambient * vec3(texture(material.diffuseTexture, texCoord));
        diffuseResult = _lightSource.diffuse * diffuseCalc * vec3(texture(material.diffuseTexture, texCoord));
    }
    else{
        ambientResult = _lightSource.ambient * material.ambient;
        diffuseResult = _lightSource.diffuse * diffuseCalc * material.diffuse;
    }

    //CHECK IF THE MATERIAL HAS A SPECULAR TEXTURE OR JUST A SPECULAR COLOR
    if(material.hasSpecularTexture == 1){
        specularResult = _lightSource.specular * specularCalc * vec3(texture(material.specularTexture, texCoord));
    }else if(material.hasSpecularTexture == 0){
        specularResult = _lightSource.specular * specularCalc * material.specular;
    }

    return (ambientResult + diffuseResult + specularResult);
}

vec3 CalculatePointLight(PointLight _lightSource, vec3 _normal, vec3 _fragPos, vec3 _viewDirection){
    vec3 lightDirection = normalize(_lightSource.position - _fragPos);

    //DIFFUSE CALCULATION
    float diffuseCalc = max(dot(_normal, lightDirection), 0.0);

    //SPECULAR CALCULATION
    vec3 reflectDiretion = reflect(-lightDirection, _normal);
    float specularCalc = pow(max(dot(_viewDirection, reflectDiretion), 0.0), material.shininess);

    //DISTANCE CALC
    float distance = length(_lightSource.position - _fragPos);
    float attenuation = 1.0 / (_lightSource.constant + _lightSource.linear * distance + _lightSource.quadratic * (distance * distance));    

    //CREATE VARIABLES TO STORE RESULTS OF PHONG SHADER
    vec3 ambientResult;
    vec3 diffuseResult;
    vec3 specularResult;

    ambientResult  *= attenuation;
    diffuseResult  *= attenuation;
    specularResult *= attenuation;
    
    //CHECK IF THE MATERIAL HAS A DIFFUSE TEXTURE OR JUST A DIFFUSE COLOR
    if(material.hasDiffuseTexture == 1){
        ambientResult = _lightSource.ambient * vec3(texture(material.diffuseTexture, texCoord));
        diffuseResult = _lightSource.diffuse * diffuseCalc * vec3(texture(material.diffuseTexture, texCoord));
    }
    else{
        ambientResult = _lightSource.ambient * material.ambient;
        diffuseResult = _lightSource.diffuse * diffuseCalc * material.diffuse;
    }

    //CHECK IF THE MATERIAL HAS A SPECULAR TEXTURE OR JUST A SPECULAR COLOR
    if(material.hasSpecularTexture == 1){
        specularResult = _lightSource.specular * specularCalc * vec3(texture(material.specularTexture, texCoord));
    }else if(material.hasSpecularTexture == 0){
        specularResult = _lightSource.specular * specularCalc * material.specular;
    }

    return (ambientResult + diffuseResult + specularResult);
}

void main ( )
{
    vec3 normal = normalize(Normal);
    vec3 viewDirection = normalize(viewPos - fragPos);

    vec3 result = CalculatePointLight(lightSource, normal, fragPos, viewDirection);

    color = vec4(result, 1.0);
}