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

void Scene::Render(Transform* _activeCamera){
    glUniform1i(glGetUniformLocation( shaders[0], "pointLightCount" ), pointLights.size());

    for(unsigned int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->Render(_activeCamera);
        activeCamera->Update();
    } 
}

void Scene::AddGameObject(GameObject* _gameObject){
    gameObjects.push_back(_gameObject);
}

void Scene::AddCamera(GameObject* _camera){
    cameras.push_back(_camera);
}

void Scene::AddPointLight(GameObject* _pointLight, LightComponent* _lightComponent){
    gameObjects.push_back(_pointLight);
    pointLights.push_back(_pointLight);

    _lightComponent->id = pointLights.size() - 1;
}
