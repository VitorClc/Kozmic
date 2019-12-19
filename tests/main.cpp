#define SDL_MAIN_HANDLED

#include <iostream>
#include <Window.h>
#include <Mesh.h>
#include <vector>

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"
"layout ( location = 1 ) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main ( )\n"
"{\n"
"gl_Position = vec4( position, 1.0 );\n"
"ourColor = color;\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 color;\n"
"void main ( )\n"
"{\n"
"color = vec4( ourColor, 1.0f );\n"
"}";

int main(){
    Window window = Window(800,600,"TESTS");

    // SHADER COMPILING 
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

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout<<"SHADER LINKING FAILED: \n"<<infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::vector<Vertex> vertices = {
        Vertex(glm::vec3(0.5, 0.5, 0.0f), glm::vec3(0.0, 1.0, 0.0)),
        Vertex(glm::vec3(0.5, -0.5, 0.0f), glm::vec3(0.0, 1.0, 0.0)),
        Vertex(glm::vec3(-0.5, -0.5, 0.0f), glm::vec3(0.0, 0.0, 1.0)),
        Vertex(glm::vec3(-0.5, 0.5, 0.0f), glm::vec3(0.0, 0.0, 1.0))
    };
    
    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2 ,3
    };

    Mesh mesh = Mesh(vertices, indices);

    while (window.isRunning())
    {
        window.Clear(0.24, 0.24, 0.24, 1.0);

        mesh.Draw(shaderProgram);
        
        window.Update();
    }

    return 0;
}