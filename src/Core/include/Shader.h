#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"
"layout ( location = 1 ) in vec2 uv;\n"
"out vec2 texCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main ( )\n"
"{\n"
"gl_Position = projection * view * model * vec4( position, 1.0 );\n"
"texCoord = vec2(uv.x, 1.0 - uv.y);\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"in vec2 texCoord;\n"
"out vec4 color;\n"
"uniform sampler2D sampler;\n"
"void main ( )\n"
"{\n"
"color = texture(sampler, texCoord);\n"
"}";

//TODO: EXTERNAL SHADER LOAD
class Shader
{
    public:
        void LoadBasic(){
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

        GLuint GetID(){
            return shaderID;
        }

    private:
        GLuint shaderID;     
};

