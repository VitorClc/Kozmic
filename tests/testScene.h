#include <Scene.h>

#include <Shader.h>
#include <Mesh.h>
#include <Transform.h>
#include <GameObject.h>
#include <Camera.h>
#include <ScriptBase.h>


class TestScene : public Scene
{
    GameObject* cameraObject;
    float cameraSpeed;

    public:
        TestScene(){
            Shader shader = Shader();
            shader.LoadBasic();

            cameraObject = new GameObject();
            cameraObject->transform->position.z = -7;
            Camera* cameraComponent = new Camera(shader.GetID(), cameraObject->transform);
            cameraObject->AddComponent(cameraComponent);

            GameObject* test = new GameObject();
            test->LoadModel("test.dae", shader.GetID());
            test->transform->scale = glm::vec3(0.5,0.5,0.5);

            AddGameObject(cameraObject);
            AddGameObject(test);
        }

        void ProcessInputs(const Uint8 *inputs, double deltaTime){
            cameraSpeed = 2.0f * deltaTime;

            if (inputs[SDL_SCANCODE_W]) {
                cameraObject->transform->position.z += 1 * cameraSpeed;
            }
            if (inputs[SDL_SCANCODE_S]) {
                cameraObject->transform->position.z -= 1 * cameraSpeed;
            }

            if (inputs[SDL_SCANCODE_A]) {
                cameraObject->transform->position.x += 1 * cameraSpeed;
            }
            if (inputs[SDL_SCANCODE_D]) {
                cameraObject->transform->position.x -= 1 * cameraSpeed;
            }

            if (inputs[SDL_SCANCODE_LSHIFT]) {
                cameraObject->transform->position.y -= 1 * cameraSpeed;
            }
            if (inputs[SDL_SCANCODE_LCTRL]) {
                cameraObject->transform->position.y += 1 * cameraSpeed;
            }
        }
};