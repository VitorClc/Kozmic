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

        void Start(){
           for(unsigned int i = 0; i < components.size(); i++){
                components[i]->Start();
            }            
        }

        void Update(){
            for(unsigned int i = 0; i < components.size(); i++){
                components[i]->Update();
            }
        }

        void AddComponent(Component* component){
            components.push_back(component);
        }
};