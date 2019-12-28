#include <Scene.h>

#include <Shader.h>
#include <Mesh.h>
#include <Transform.h>
#include <GameObject.h>
#include <Camera.h>
#include <ScriptBase.h>

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

class TestScene : public Scene
{
    public:
        TestScene(){
            Shader shader = Shader();
            shader.LoadBasic();

            GameObject* cameraObject = new GameObject();
            cameraObject->transform->position.z = -7;
            Camera* cameraComponent = new Camera(shader.GetID(), cameraObject->transform);
            cameraObject->AddComponent(cameraComponent);

            GameObject* test = new GameObject();
            test->LoadModel("test.dae", shader.GetID());
            RotateCube* rotate = new RotateCube(test);
            test->AddComponent(rotate);
            test->transform->scale = glm::vec3(0.5,0.5,0.5);
  
            GameObject* test2 = new GameObject();
            test2->LoadModel("test2.dae", shader.GetID());
            test2->transform->position.y = 3;

            GameObject* test3 = new GameObject();
            test3->LoadModel("test3.dae", shader.GetID());
            test3->transform->position.x = 3;

            GameObject* test4 = new GameObject();
            test4->LoadModel("test3.dae", shader.GetID());
            RotateCube* rotate2 = new RotateCube(test4);
            test4->AddComponent(rotate2);
            test4->transform->position.x = -3;

            AddGameObject(cameraObject);
            AddGameObject(test);
            AddGameObject(test2);
            AddGameObject(test3);
            AddGameObject(test4);
        }
};