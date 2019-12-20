#include <Window.h>

//TODO: ADD LOGS
Window::Window(unsigned int width, unsigned int height, const char* title){
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    glContext = SDL_GL_CreateContext( window );
    
    glewInit();
    glEnable(GL_DEPTH_TEST);
    
    running = true;
}

bool Window::isRunning(){
    return running;
}

void Window::Clear(float r, float g, float b, float a){
    glClearColor (r, g, b, a);
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Window::Update(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            running = false;
        }
    }

    SDL_GL_SwapWindow(window);
}

Window::~Window(){
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}