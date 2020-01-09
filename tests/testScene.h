#include <Scene.h>

#include <Shader.h>
#include <Mesh.h>
#include <Transform.h>
#include <GameObject.h>
#include <Camera.h>
#include <ScriptBase.h>
#include <Light.h>

class TestScene : public Scene
{
    GameObject* cameraObject;
    float cameraSpeed;
    float movSpeed;

    float lastX = 1024 / 2.0f;
    float lastY = 720 / 2.0f;

    float sensitivity = 0.1;

    public:
        TestScene(){
            Shader shader = Shader("basic.vert", "basic.frag");
            shaders.push_back(shader.GetID());

            Shader shader2 = Shader("emissive.vert", "emissive.frag");
            shaders.push_back(shader2.GetID());

            cameraObject = new GameObject();
            cameraObject->transform->position.z = -7;
            cameraObject->transform->position.y = 3;
            cameraObject->transform->rotation.y = 90;
            cameraObject->transform->rotation.x = -30;
            Camera* cameraComponent = new Camera(shaders, cameraObject->transform);
            cameraObject->AddComponent(cameraComponent);

            AddCamera(cameraObject);
            activeCamera = cameras[0];

            GameObject* light = new GameObject();
            LightComponent* lightComponent = new LightComponent(shader.GetID(), light->transform, 2);
            light->AddComponent(lightComponent);
            light->transform->position = glm::vec3(0.0, 3.0, 3.0);
            light->transform->scale = glm::vec3(0.5,0.5,0.5);
            AddPointLight(light, lightComponent);

            GameObject* test = new GameObject();
            test->LoadModel("testScene.obj", shader.GetID());
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
        }
};