#define SDL_MAIN_HANDLED
#define GLEW_STATIC

#include <SDL.h>
#include <GL/glew.h>

int main(int argc, char const *argv[])
{
    SDL_Window *window;
    SDL_GLContext context;

    bool running = true;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Kozmic TESTS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext( window );
    
    glewInit();
    
    glClearColor ( 0.24f, 0.24f, 0.24f, 1.0 );
    
    while(running == true){
        SDL_GL_SwapWindow(window);

        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        glClear ( GL_COLOR_BUFFER_BIT );
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
