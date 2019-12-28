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

            AddGameObject(cameraObject);
            AddGameObject(test);
        }
};