#pragma once

#include <vector>

#include <Component.h>
#include <Transform.h>

class GameObject
{
    private:
        std::vector<Component*> components;
    
    public:
        Transform* transform;
        
        GameObject();

        void Start();

        void Update();

        void AddComponent(Component* component);
};