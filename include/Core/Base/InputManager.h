#include <SDL.h>

class Keyboard{
    public:
        void ProcessInputs(SDL_Event _event){
            keys = SDL_GetKeyboardState(NULL);
            event = _event;
        }
        
        bool GetKey(SDL_Scancode key){
            return keys[key];
        }

        bool GetKeyDown(SDL_Scancode key){
            if(event.type == SDL_KEYDOWN && event.key.repeat == 0){
                if(event.key.keysym.scancode == key){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }

        bool GetKeyUp(SDL_Scancode key){
            if(event.type == SDL_KEYUP && event.key.repeat == 0){
                if(event.key.keysym.scancode == key){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }

    private:
        const Uint8 *keys;
        
        SDL_Event event;
};

class Mouse{
    public:
        int xPosition;
        int yPosition;
        bool leftButton;
        bool rightButton;
};

class InputManager{
    public:
        Keyboard keyboard = Keyboard();
        Mouse mouse = Mouse();
};
