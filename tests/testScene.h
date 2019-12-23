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
            std::cout<<counter<<std::endl;
        }
};

class TestScene : public Scene
{
    public:
        TestScene(){
            std::vector<Vertex> vertices = {
                Vertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0.0, 0.0)),
                Vertex(glm::vec3(0.5, -0.5, 0.5), glm::vec2(1.0, 0.0)),
                Vertex(glm::vec3(0.5, 0.5, 0.5), glm::vec2(1.0, 1.0)),
                Vertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec2(0.0, 1.0)),

                Vertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec2(1.0, 1.0)),
                Vertex(glm::vec3(0.5, -0.5, -0.5), glm::vec2(1.0, 0.0)),
                Vertex(glm::vec3(0.5, 0.5, -0.5), glm::vec2(0.0, 0.0)),
                Vertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec2(1.0, 1.0))
            };
            
            std::vector<unsigned int> indices = {
                // front
                0, 1, 2,
                2, 3, 0,
                // top
                3, 2, 6,
                6, 7, 3,
                // back
                7, 6, 5,
                5, 4, 7,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // left
                4, 0, 3,
                3, 7, 4,
                // right
                1, 5, 6,
                6, 2, 1,
            };

            Shader shader = Shader();
            shader.LoadBasic();

            GameObject* cameraObject = new GameObject();
            cameraObject->transform->position.z = -3;
            Camera* cameraComponent = new Camera(shader.GetID(), cameraObject->transform);
            cameraObject->AddComponent(cameraComponent);

            GameObject* test = new GameObject();
            Mesh* mesh = new Mesh(vertices, indices, shader.GetID(), test->transform);
            RotateCube* rotateCubeScript = new RotateCube(test);
            mesh->AddTexture("test.jpg");
            test->AddComponent(mesh);
            test->AddComponent(rotateCubeScript);

            test->transform->rotation.x = 0.55;
            test->transform->scale = glm::vec3(0.5, 0.5, 0.5);

            AddGameObject(cameraObject);
            AddGameObject(test);
        }
};