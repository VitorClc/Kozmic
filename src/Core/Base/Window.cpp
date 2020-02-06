#include <Base/Window.h>

//TODO: ADD LOGS
Window::Window(unsigned int _width, unsigned int _height, const char* title){
    SDL_Init(SDL_INIT_VIDEO);

    width = _width;
    height = _height;

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
    inputManager.keyboard.ProcessInputs(event);

    //GET MOUSE POS
    SDL_GetMouseState(&inputManager.mouse.xPosition, &inputManager.mouse.yPosition );

    //GET MOUSE BUTTON
    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
        inputManager.mouse.leftButton = true;
    }
    else{
        inputManager.mouse.leftButton = false;
    }

    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)){
        inputManager.mouse.rightButton = true;
    }
    else{
        inputManager.mouse.rightButton = false;
    }
}

void Window::Update(){
    SDL_GL_SwapWindow(window);
}

void Window::Exit(){
    running = false;
}

SDL_Window* Window::GetSDLWindow(){
    return window;
}

SDL_GLContext Window::GetGLContext(){
    return glContext;
}

Window::~Window(){
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}