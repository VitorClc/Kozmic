#define SDL_MAIN_HANDLED

#include <Base/Window.h>
#include <Base/PhysicsManager.h>

#include <testScene.h>

int main(){
    Window window = Window(1024,720,"TESTS");
    PhysicsManager* physicsManager = new PhysicsManager();

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
		testScene.UpdatePhysics(physicsManager->dynamicsWorld);
        testScene.Update();
        testScene.Render(testScene.activeCamera->transform);
        
        window.Update();
    }

    return 0;
}