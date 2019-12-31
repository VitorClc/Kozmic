#include <Scene.h>

void Scene::Start(){
    for(unsigned int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->Start();
    }
}

void Scene::Update(){
    
    for(unsigned int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->Update();
    }
}

void Scene::AddGameObject(GameObject* _gameObject){
    gameObjects.push_back(_gameObject);
}
