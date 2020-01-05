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
            cameraObject->transform->position.z = 7;
            cameraObject->transform->rotation.y = -90;
            Camera* cameraComponent = new Camera(shaders, cameraObject->transform);
            cameraObject->AddComponent(cameraComponent);
            cameraObject->transform->position.y = 7;
            cameraObject->transform->position.z = 10;

            AddCamera(cameraObject);
            activeCamera = cameras[0];

            GameObject* test = new GameObject();
            test->LoadModel("test.dae", shader.GetID());

            light = new GameObject();
            light->LoadModel("test.dae", shader2.GetID());
            light->transform->position.x = 3;
            light->transform->position.y = 8;
            light->transform->position.z = 4;
            light->transform->scale = glm::vec3(0.5,0.5,0.5);
            
            AddGameObject(light);
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

            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)){
                cameraObject->transform->rotation.x += xoffset;
                cameraObject->transform->rotation.y += yoffset;

                if (inputManager.keyboard.keys[SDL_SCANCODE_W]) {
                    cameraObject->transform->position += cameraObject->transform->front * cameraSpeed;
                }
                if (inputManager.keyboard.keys[SDL_SCANCODE_S]) {
                    cameraObject->transform->position -= cameraObject->transform->front * cameraSpeed;
                }

                if (inputManager.keyboard.keys[SDL_SCANCODE_A]) {
                    cameraObject->transform->position -= cameraObject->transform->right * cameraSpeed;
                }
                if (inputManager.keyboard.keys[SDL_SCANCODE_D]) {
                    cameraObject->transform->position += cameraObject->transform->right * cameraSpeed;
                }

                if (inputManager.keyboard.keys[SDL_SCANCODE_SPACE]) {
                    cameraObject->transform->position.y += 1 * cameraSpeed;
                }
                if (inputManager.keyboard.keys[SDL_SCANCODE_LCTRL]) {
                    cameraObject->transform->position.y -= 1 * cameraSpeed;
                }

                if (inputManager.keyboard.keys[SDL_SCANCODE_LSHIFT]) {
                    cameraSpeed = 10.0f * deltaTime;
                }else{
                    cameraSpeed = 5.0f * deltaTime;
                }
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
                light->transform->position.y += 1 * movSpeed;
            }
            if (inputManager.keyboard.keys[SDL_SCANCODE_RCTRL]) {
                light->transform->position.y -= 1 * movSpeed;
            }   
        }
};