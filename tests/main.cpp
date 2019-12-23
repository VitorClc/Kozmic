#define SDL_MAIN_HANDLED

#include <Window.h>
#include <testScene.h>

int main(){
    Window window = Window(1024,720,"TESTS");

    TestScene testScene = TestScene();
    testScene.Start();

    while (window.isRunning())
    {
        window.Clear(0.24, 0.24, 0.24, 1.0);

        testScene.Update();

        window.Update();
    }

    return 0;
}