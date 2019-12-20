#include <vector>

#include <Component.h>
#include <Transform.h>

class GameObject
{
    private:
        std::vector<Component*> components;
    
    public:
        Transform* transform = new Transform();
        
        GameObject(){
            AddComponent(transform);
        }

        void AddComponent(Component* component){
            components.push_back(component);
        }
};