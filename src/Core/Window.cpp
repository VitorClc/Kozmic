#include <Window.h>

//TODO: ADD LOGS
Window::Window(unsigned int width, unsigned int height, const char* title){
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    glContext = SDL_GL_CreateContext( window );
    
    glewInit();

    glViewport(0,0, width, height);

    glEnable(GL_DEPTH_TEST);
    
    running = true;
}

bool Window::IsRunning(){
    return running;
}

void Window::Clear(float r, float g, float b, float a){
    glClearColor (r, g, b, a);
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Window::ProcessInputs(){
    SDL_PumpEvents();

    //DETECT EXIT
    SDL_Event event;

    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        Exit();
    }

    //GET KEYBOARD INPUTS
    inputs = SDL_GetKeyboardState(NULL);
}
void Window::Update(){
    SDL_GL_SwapWindow(window);
}

void Window::Exit(){
    running = false;
}

Window::~Window(){
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}