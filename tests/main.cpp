#define SDL_MAIN_HANDLED

#include <Window.h>
#include <testScene.h>

int main(){
    Window window = Window(1024,720,"TESTS");
    
    TestScene testScene = TestScene();
    testScene.Start();

    SDL_Event event;

    float startTime = SDL_GetTicks();
    float lastTime = SDL_GetTicks();

    while (window.IsRunning())
    {
        startTime = SDL_GetTicks();
        float deltaTime = (startTime - lastTime) / 1000.0f;
        lastTime = startTime;

        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                window.Exit();
            }
        }

        window.Clear(0.24, 0.24, 0.24, 1.0);

        testScene.Update();
        window.Update();
    }

    return 0;
}