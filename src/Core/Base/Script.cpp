#include <Base/Script.h>

Script::Script(GameObject* _gameObject){
    gameObject = _gameObject;
    transform = _gameObject->transform;
}