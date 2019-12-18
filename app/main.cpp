#define SDL_MAIN_HANDLED
#define GLEW_STATIC

#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"
"layout ( location = 1 ) in vec3 color;\n"
"out vec3 ourColor;\n"
"uniform mat4 transform;\n"
"void main ( )\n"
"{\n"
"gl_Position = transform * vec4( position, 1.0 );\n"
"ourColor = color;\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 color;\n"
"void main ( )\n"
"{\n"
"color = vec4( ourColor, 1.0f );\n"
"}";

int main(int argc, char const *argv[])
{
    // WINDOW AND OPENGL CONTEXT CREATION 
    SDL_Window *window;
    SDL_GLContext context;

    bool running = true;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Kozmic TESTS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext( window );
    
    glewInit();
    
    glClearColor (0.24f, 0.24f, 0.24f, 1.0);
    //////////////////////////////////////

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

    GLfloat Vertices[] = {
        /// VERTICES            COLORS
        0.5f,  0.5f, 0.0f,       0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,       0.0f, 1.0f, 0.0f
    };

    GLint Indices[] = {
        0, 1, 3,
        1, 2, 3
    }; 

    GLuint VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    // COLOR BUFFER
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    //

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(running == true){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        glClear ( GL_COLOR_BUFFER_BIT );

        glUseProgram(shaderProgram);
        
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(1, -0.5f, 0.0f));
    
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
