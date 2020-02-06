#include <Base/Component.h>
#include <Base/GameObject.h>
#include <Components/Transform.h>

class Script : public Component
{
    public:
        GameObject* gameObject;
        Transform* transform;
        
        Script(GameObject* _gameObject);

        virtual void Start() = 0;
        virtual void Update() = 0;
};
