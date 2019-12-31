#define GLEW_STATIC

#include <SDL.h>
#include <GL/glew.h>

class Window{
    public:
        Window(unsigned int width, unsigned int height, const char* title);
        
        bool IsRunning();
        
        void Clear(float r, float g, float b, float a);

        void ProcessInputs();
        void Update();
        
        void Exit();
        
        ~Window();

        const Uint8 *inputs;
        
    private:
        SDL_Window *window;
        SDL_GLContext glContext;
        
        bool running;
};