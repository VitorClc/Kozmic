#include <GameObject.h>

GameObject::GameObject(){
    transform = new Transform();
    AddComponent(transform);
}

void GameObject::Start(){
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Start();
    }     
}

void GameObject::Update(){
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Update();
    }
}

void GameObject::AddComponent(Component* component){
    components.push_back(component);
}