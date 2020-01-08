#define SDL_MAIN_HANDLED

#include <Window.h>
#include <testScene.h>

int main(){
    Window window = Window(1024,720,"TESTS");
    
    TestScene testScene = TestScene();
    testScene.Start();

    float startTime = SDL_GetTicks();
    float lastTime = SDL_GetTicks();

    while (window.IsRunning())
    {
        startTime = SDL_GetTicks();
        float deltaTime = (startTime - lastTime) / 1000.0f;
        lastTime = startTime;

        window.Clear(0.24, 0.24, 0.24, 1.0);
        window.ProcessInputs();
        
        testScene.ProcessInputs(window.inputManager, deltaTime);
        testScene.Update();
        testScene.Render(testScene.activeCamera->transform);

        window.Update();
    }

    return 0;
}