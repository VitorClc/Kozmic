#include <Component.h>
#include <GameObject.h>
#include <Transform.h>

class ScriptBase : public Component
{
    public:
        GameObject* gameObject;
        Transform* transform;
        
        ScriptBase(GameObject* _gameObject);

        virtual void Start() = 0;
        virtual void Update() = 0;
};
