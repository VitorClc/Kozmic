#include <Scene.h>

#include <Shader.h>
#include <Mesh.h>
#include <Transform.h>
#include <GameObject.h>
#include <Camera.h>
#include <ScriptBase.h>

#include <iostream>

class RotateCube : public ScriptBase{
    public:
        float counter = 0;

        RotateCube(GameObject* _gameObject) : ScriptBase(_gameObject){};

        void Start(){
            
        }

        void Update(){
            counter += 0.0001f;
            transform->rotation.y += counter;
        }
};

class RotateChildren : public ScriptBase{
    public:
        float counter = 0;

        RotateChildren(GameObject* _gameObject) : ScriptBase(_gameObject){};

        void Start(){
            
        }

        void Update(){
            counter -= 0.0001f;
            transform->rotation.x += counter;
        }
};

class TestScene : public Scene
{
    public:
        TestScene(){
            Shader shader = Shader();
            shader.LoadBasic();

            GameObject* cameraObject = new GameObject();
            cameraObject->transform->position.z = -3;
            Camera* cameraComponent = new Camera(shader.GetID(), cameraObject->transform);
            cameraObject->AddComponent(cameraComponent);

            GameObject* test = new GameObject();
            test->LoadModel("test.dae", shader.GetID());
            RotateCube* rotate = new RotateCube(test);
            test->AddComponent(rotate);
            
            AddGameObject(cameraObject);
            AddGameObject(test);
        }
};