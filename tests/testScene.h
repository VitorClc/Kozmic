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
    float movSpeed;

    float lastX = 1024 / 2.0f;
    float lastY = 720 / 2.0f;

    float sensitivity = 0.1;


    public:
        GameObject* light;

        TestScene(){
            std::vector<GLuint> shaders;

            Shader shader = Shader();
            shader.LoadBasic();
            shaders.push_back(shader.GetID());

            Shader shader2 = Shader();
            shader2.LoadLamp();
            shaders.push_back(shader2.GetID());

            cameraObject = new GameObject();
            cameraObject->transform->position.z = -7;
            cameraObject->transform->rotation.y = 90;
            Camera* cameraComponent = new Camera(shaders, cameraObject->transform);
            cameraObject->AddComponent(cameraComponent);

            AddCamera(cameraObject);
            activeCamera = cameras[0];

            GameObject* test = new GameObject();
            test->LoadModel("monkey.dae", shader.GetID());

            light = new GameObject();
            light->LoadModel("test.dae", shader2.GetID());
            light->transform->position.x = -4;
            light->transform->position.y = -2;
            light->transform->scale = glm::vec3(0.5,0.5,0.5);
            
            AddGameObject(light);
            AddGameObject(test);
        }

        void ProcessInputs(InputManager inputManager, double deltaTime){
            float xpos = inputManager.mouse.yPosition;
            float ypos = inputManager.mouse.xPosition;

            float xoffset = xpos - lastX;
            float yoffset = ypos - lastY; 
            lastX = xpos;
            lastY = ypos;

            xoffset *= sensitivity;
            yoffset *= sensitivity;

            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)){
                cameraObject->transform->rotation.x -= xoffset;
                cameraObject->transform->rotation.y += yoffset;
            }
            cameraSpeed = 2.0f * deltaTime;
            movSpeed = 2.0f * deltaTime;

            if (inputManager.keyboard.keys[SDL_SCANCODE_W]) {
                cameraObject->transform->position.z += 1 * cameraSpeed;
            }
            if (inputManager.keyboard.keys[SDL_SCANCODE_S]) {
                cameraObject->transform->position.z -= 1 * cameraSpeed;
            }

            if (inputManager.keyboard.keys[SDL_SCANCODE_A]) {
                cameraObject->transform->position.x += 1 * cameraSpeed;
            }
            if (inputManager.keyboard.keys[SDL_SCANCODE_D]) {
                cameraObject->transform->position.x -= 1 * cameraSpeed;
            }

            if (inputManager.keyboard.keys[SDL_SCANCODE_LSHIFT]) {
                cameraObject->transform->position.y += 1 * cameraSpeed;
            }
            if (inputManager.keyboard.keys[SDL_SCANCODE_LCTRL]) {
                cameraObject->transform->position.y -= 1 * cameraSpeed;
            }

            //COntrol light
            if (inputManager.keyboard.keys[SDL_SCANCODE_UP]) {
                light->transform->position.z += 1 * movSpeed;
            }
            if (inputManager.keyboard.keys[SDL_SCANCODE_DOWN]) {
                light->transform->position.z -= 1 * movSpeed;
            }

            if (inputManager.keyboard.keys[SDL_SCANCODE_LEFT]) {
                light->transform->position.x += 1 * movSpeed;
            }
            if (inputManager.keyboard.keys[SDL_SCANCODE_RIGHT]) {
                light->transform->position.x -= 1 * movSpeed;
            }
            
            if (inputManager.keyboard.keys[SDL_SCANCODE_RSHIFT]) {
                light->transform->position.y += 1 * cameraSpeed;
            }
            if (inputManager.keyboard.keys[SDL_SCANCODE_RCTRL]) {
                light->transform->position.y -= 1 * cameraSpeed;
            }
        }
};