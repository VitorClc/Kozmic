#include <GameObject.h>

GameObject::GameObject(){
    transform = new Transform();
    AddComponent(transform);
}

void GameObject::Start(){
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Start();
    }     

    //START CHILDREN
    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->Start();
    }     
}

void GameObject::Update(){
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Update();
    }

    //UPDATE CHILDREN
    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->Update();
    }
}

void GameObject::AddComponent(Component* component){
    components.push_back(component);
}

void GameObject::AddChild(GameObject* _child){
    children.push_back(_child);
    _child->transform->SetParent(this->transform);
}