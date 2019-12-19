#define SDL_MAIN_HANDLED

#include <iostream>
#include <Window.h>

int main(){
    Window window = Window(800,600,"TESTS");

    while (window.isRunning())
    {
        window.Clear(0.24, 0.24, 0.24, 1.0);

        window.Update();
    }

    return 0;
}