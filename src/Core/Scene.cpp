#include <Scene.h>

void Scene::Start(){
    for(unsigned int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->Start();
    }

    for(unsigned int i = 0; i < cameras.size(); i++){
        cameras[i]->Start();
    }
}

void Scene::Update(){
    for(unsigned int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->Update();
    } 
}

void Scene::Render(){
    for(unsigned int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->Render();
        activeCamera->Update();
    } 
}

void Scene::AddGameObject(GameObject* _gameObject){
    gameObjects.push_back(_gameObject);
}

void Scene::AddCamera(GameObject* _camera){
    cameras.push_back(_camera);
}
