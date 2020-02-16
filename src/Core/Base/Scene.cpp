#include <Base/Scene.h>

void Scene::Start(){

    Renderer* rootRenderer = new Renderer();
    rootGameObject->SetRenderer(rootRenderer);

    rootGameObject->Start();

    for(unsigned int i = 0; i < cameras.size(); i++){
        cameras[i]->Start();
    }
}

void Scene::UpdatePhysics(btDiscreteDynamicsWorld* dynamicsWorld){

}

void Scene::Update(){
    rootGameObject->Update();
}

void Scene::Render(Transform* _activeCamera){
    glUniform1i(glGetUniformLocation( shaderManager.GetShader(0), "pointLightCount" ), pointLights.size());

    for(unsigned int shader = 0; shader < shaderManager.ShaderAmount(); shader++){
        rootGameObject->Render(_activeCamera, shaderManager.GetShader(shader));     
        activeCamera->Update();
    }
}

void Scene::AddGameObject(GameObject* _gameObject){
    gameObjects.push_back(_gameObject);
    rootGameObject->AddChild(_gameObject);
}

void Scene::AddCamera(GameObject* _camera){
    cameras.push_back(_camera);
}

void Scene::AddPointLight(GameObject* _pointLight, LightComponent* _lightComponent){
    gameObjects.push_back(_pointLight);
    pointLights.push_back(_pointLight);
    rootGameObject->AddChild(_pointLight);

    _lightComponent->id = pointLights.size() - 1;
}

void Scene::SetDirectionalLight(GameObject* _light){
    gameObjects.push_back(_light);
    directionalLight = _light;
}