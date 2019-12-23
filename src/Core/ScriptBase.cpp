#include <ScriptBase.h>

ScriptBase::ScriptBase(GameObject* _gameObject){
    gameObject = _gameObject;
    transform = _gameObject->transform;
}