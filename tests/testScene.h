#include <Base/Scene.h>
#include <Base/GameObject.h>
#include <Base/Script.h>

#include <Renderers/MeshRenderer.h>

#include <Components/Transform.h>
#include <Components/Camera.h>
#include <Components/Light.h>

#include <Base/Shader.h>

class TestScene : public Scene
{
    GameObject* cameraObject;

    float cameraSpeed;
    float movSpeed;

    float lastX = 1024 / 2.0f;
    float lastY = 720 / 2.0f;

    float sensitivity = 0.1;

    public:
        GameObject* light;

        TestScene(){
            cameraObject = new GameObject();
            cameraObject->transform->position.z = -7;
            cameraObject->transform->position.y = 3;
            cameraObject->transform->rotation.y = 90;
            cameraObject->transform->rotation.x = -30;
            Camera* cameraComponent = new Camera(cameraObject->transform);
            cameraObject->AddComponent(cameraComponent);

            AddCamera(cameraObject);
            activeCamera = cameras[0];

            light = new GameObject();
            LightComponent* lightComponent = new LightComponent(light->transform, 2);
            light->LoadModel("lamp.obj");
            light->AddComponent(lightComponent);
            light->transform->position = glm::vec3(0.0, 3.0, 3.0);
            AddPointLight(light, lightComponent);

            GameObject* test = new GameObject();
            test->LoadModel("testScene.obj");
            AddGameObject(test);
        }

        void ProcessInputs(InputManager inputManager, double deltaTime){
            movSpeed = 10.0f * deltaTime;

            float xpos = inputManager.mouse.yPosition;
            float ypos = inputManager.mouse.xPosition;

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos; 
            lastX = xpos;
            lastY = ypos;

            xoffset *= sensitivity;
            yoffset *= sensitivity;

            if(inputManager.mouse.leftButton == true){
                cameraObject->transform->rotation.x += xoffset;
                cameraObject->transform->rotation.y += yoffset;

                if (inputManager.keyboard.GetKey(SDL_SCANCODE_W)) {
                    cameraObject->transform->position += cameraObject->transform->front * cameraSpeed;
                }
                if (inputManager.keyboard.GetKey(SDL_SCANCODE_S)) {
                    cameraObject->transform->position -= cameraObject->transform->front * cameraSpeed;
                }

                if (inputManager.keyboard.GetKey(SDL_SCANCODE_A)) {
                    cameraObject->transform->position -= cameraObject->transform->right * cameraSpeed;
                }
                if (inputManager.keyboard.GetKey(SDL_SCANCODE_D)) {
                    cameraObject->transform->position += cameraObject->transform->right * cameraSpeed;
                }

                if (inputManager.keyboard.GetKey(SDL_SCANCODE_SPACE)) {
                    cameraObject->transform->position.y += 1 * cameraSpeed;
                }
                if (inputManager.keyboard.GetKey(SDL_SCANCODE_LCTRL)) {
                    cameraObject->transform->position.y -= 1 * cameraSpeed;
                }

                if (inputManager.keyboard.GetKey(SDL_SCANCODE_LSHIFT)) {
                    cameraSpeed = 10.0f * deltaTime;
                }else{
                    cameraSpeed = 5.0f * deltaTime;
                }
            }
            
            if (inputManager.keyboard.GetKey(SDL_SCANCODE_UP)) {
                light->transform->position.z += 1 * movSpeed;
            }
            if (inputManager.keyboard.GetKey(SDL_SCANCODE_DOWN)) {
                light->transform->position.z -= 1 * movSpeed;
            }
            if (inputManager.keyboard.GetKey(SDL_SCANCODE_LEFT)) {
                light->transform->position.x += 1 * movSpeed;
            }
            if (inputManager.keyboard.GetKey(SDL_SCANCODE_RIGHT)) {
                light->transform->position.x -= 1 * movSpeed;
            }
        }
};