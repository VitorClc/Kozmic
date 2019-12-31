#include <SDL.h>

class Keyboard{
    public:
        const Uint8 *keys;
};

class Mouse{
    public:
        int xPosition;
        int yPosition;
};

class InputManager{
    public:
        Keyboard keyboard = Keyboard();
        Mouse mouse = Mouse();
};
