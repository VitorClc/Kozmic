#include <Shader.h>

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"
"layout ( location = 1 ) in vec2 uv;\n"
"layout ( location = 2 ) in vec3 normal;\n"

"out vec2 texCoord;\n"
"out vec3 Normal;\n"
"out vec3 fragPos;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main ( )\n"
"{\n"
"gl_Position = projection * view * model * vec4( position, 1.0 );\n"
"fragPos = vec3(model * vec4(position, 1.0f));\n"
"Normal = mat3(transpose(inverse(model))) * normal;\n"
"texCoord = uv;\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"struct Material{\n"
    "vec3 ambient;\n"
    "vec3 diffuse;\n"
    "vec3 specular;\n"
    "sampler2D diffuseTexture;\n"
    "int hasDiffuseTexture;\n"
    "sampler2D specularTexture;\n"
    "int hasSpecularTexture;\n"
    "float shininess;\n"
"};\n"

"struct Light{\n"
    "vec3 position;\n"
    "vec3 ambient;\n"
    "vec3 diffuse;\n"
    "vec3 specular;\n"
"};\n"

"out vec4 color;\n"

"in vec3 fragPos;\n"
"in vec3 Normal;\n"
"in vec2 texCoord;\n"

"uniform vec3 viewPos;\n"
"uniform Material material;\n"
"uniform Light light;\n"

"vec3 ambientResult;\n"
"vec3 diffuseResult;\n"
"vec3 specularResult;\n"

"void main ( )\n"
"{\n"
// Ambient
"if(material.hasDiffuseTexture == 1){\n"
"ambientResult = light.ambient * vec3(texture(material.diffuseTexture, texCoord));\n"
"}else if(material.hasDiffuseTexture == 0){\n"
"ambientResult = light.ambient * material.ambient;\n"
"}\n"

// Diffuse
"vec3 norm = normalize(Normal);\n"
"vec3 lightDir = normalize(light.position - fragPos);\n"
"float diff = max(dot(norm, lightDir), 0.0);\n"
"diffuseResult = light.diffuse * diff * material.diffuse;\n"

// Specular
"vec3 viewDir = normalize(viewPos - fragPos);\n"
"vec3 reflectDir = reflect(-lightDir, norm);\n"
"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
"if(material.hasSpecularTexture == 1){\n"
"specularResult = light.specular * spec * vec3(texture(material.specularTexture, texCoord));\n"
"}else if(material.hasSpecularTexture == 0){\n"
"specularResult = light.specular * spec * material.specular;\n"
"}\n"

"if(material.hasDiffuseTexture == 1){\n"
"color = texture(material.diffuseTexture, texCoord) * vec4(ambientResult + diffuseResult + specularResult, 1.0f);\n"
"}else{\n"
"color = vec4(ambientResult + diffuseResult + specularResult, 1.0f);"
"}\n"
"}";

const GLchar *lampVS = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main ( )\n"
"{\n"
"gl_Position = projection * view * model * vec4( position, 1.0 );\n"
"}";

const GLchar *lampFS = "#version 330 core\n"
"out vec4 color;\n"

"void main ( )\n"
"{\n"
"color = vec4(1.0f);\n"
"}";

void Shader::LoadBasic(){
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource( vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout<<"VERTEX SHADER COMPILATION FAILED: \n"<<infoLog << std::endl;
    }    

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout<<"FRAGMENT SHADER COMPILATION FAILED: \n"<<infoLog << std::endl;
    }    

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);

    glGetShaderiv(shaderID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout<<"SHADER LINKING FAILED: \n"<<infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::LoadLamp(){
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource( vertexShader, 1, &lampVS, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout<<"VERTEX SHADER COMPILATION FAILED: \n"<<infoLog << std::endl;
    }    

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &lampFS, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout<<"FRAGMENT SHADER COMPILATION FAILED: \n"<<infoLog << std::endl;
    }    

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);

    glGetShaderiv(shaderID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout<<"SHADER LINKING FAILED: \n"<<infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::GetID(){
    return shaderID;
}