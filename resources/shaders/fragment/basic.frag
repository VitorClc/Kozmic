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

struct Light{
    vec3 position;
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
uniform Light light;

vec3 ambientResult;
vec3 diffuseResult;
vec3 specularResult;

void main ( )
{
    // Ambient
    if(material.hasDiffuseTexture == 1){
        ambientResult = light.ambient * vec3(texture(material.diffuseTexture, texCoord));
    }else if(material.hasDiffuseTexture == 0){
        ambientResult = light.ambient * material.ambient;
    }

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    diffuseResult = light.diffuse * diff * material.diffuse;

    // Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    if(material.hasSpecularTexture == 1){
        specularResult = light.specular * spec * vec3(texture(material.specularTexture, texCoord));
    }else if(material.hasSpecularTexture == 0){
        specularResult = light.specular * spec * material.specular;
    }

    if(material.hasDiffuseTexture == 1){
        color = texture(material.diffuseTexture, texCoord) * vec4(ambientResult + diffuseResult + specularResult, 1.0f);
    }else{
        color = vec4(ambientResult + diffuseResult + specularResult, 1.0f);
    }
}