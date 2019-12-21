#define SDL_MAIN_HANDLED
#define GLEW_STATIC

#include <iostream>
#include <Window.h>
#include <Mesh.h>
#include <Transform.h>
#include <GameObject.h>

#include <vector>

#include <GL/glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
        Vertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0.0, 0.0)),
        Vertex(glm::vec3(0.5, -0.5, 0.5), glm::vec2(1.0, 0.0)),
        Vertex(glm::vec3(0.5, 0.5, 0.5), glm::vec2(1.0, 1.0)),
        Vertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec2(0.0, 1.0)),

        Vertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec2(1.0, 1.0)),
        Vertex(glm::vec3(0.5, -0.5, -0.5), glm::vec2(1.0, 0.0)),
        Vertex(glm::vec3(0.5, 0.5, -0.5), glm::vec2(0.0, 0.0)),
        Vertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec2(1.0, 1.0))
    };
    
    std::vector<unsigned int> indices = {
        // front
        0, 1, 2,
        2, 3, 0,
        // top
        3, 2, 6,
        6, 7, 3,
        // back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // left
        4, 0, 3,
        3, 7, 4,
        // right
        1, 5, 6,
        6, 2, 1,
    };

    glm::mat4 projection;
    projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

    GameObject test = GameObject();
    Mesh* mesh = new Mesh(vertices, indices, shaderProgram, test.transform);
    mesh->AddTexture("test.jpg");

    test.AddComponent(mesh);

    test.transform->rotation.x = 0.55;
    test.transform->scale = glm::vec3(0.5, 0.5, 0.5);

    test.Start();

    Transform cameraPosition = Transform();
    cameraPosition.position = glm::vec3(0.0, 0.0, -3.0);

    float counter = 0;

    while (window.isRunning())
    {
        window.Clear(0.24, 0.24, 0.24, 1.0);
                
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cameraPosition.getMatrix()));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        test.transform->rotation.x = counter;
        test.transform->rotation.y = counter;

        counter += 0.01f;

        test.Update();

        window.Update();
    }

    return 0;
}