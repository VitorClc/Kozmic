#pragma once

#include <vector>

#include <Component.h>
#include <Transform.h>

class GameObject
{
    private:
        std::vector<Component*> components;
        std::vector<GameObject*> children;
    
    public:
        Transform* transform;
        
        GameObject();

        void Start();

        void Update();

        void AddComponent(Component* component);

        void AddChild(GameObject* _child);
};