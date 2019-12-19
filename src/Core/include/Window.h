#define GLEW_STATIC

#include <string>

#include <SDL.h>
#include <GL/glew.h>

class Window{
    public:
        Window(unsigned int width, unsigned int height, const char* title);
        
        bool isRunning();
        
        void Clear(float r, float g, float b, float a);
        void Update();

        ~Window();

    private:
        SDL_Window *window;
        SDL_GLContext glContext;
        
        bool running;
};