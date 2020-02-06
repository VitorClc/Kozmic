#pragma once

#define GLEW_STATIC

#include <SDL.h>
#include <GL/glew.h>
#include <Base/InputManager.h>

class Window{
    public:
        Window(unsigned int _width, unsigned int _height, const char* title);
        
        bool IsRunning();
        
        void Clear(float r, float g, float b, float a);

        void ProcessInputs();
        void Update();
        
        void Exit();

        SDL_GLContext GetGLContext();
        SDL_Window* GetSDLWindow();

        ~Window();

        InputManager inputManager;
        
        int width, height;

    private:
        SDL_Window *window;
        SDL_GLContext glContext;
        
        bool running;
};