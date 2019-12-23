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

            GameObject* transformTest = new GameObject();
            RotateChildren* rotateCubeScript2 = new RotateChildren(transformTest);
            test->AddComponent(rotateCubeScript2);
            test->AddChild(transformTest);

            GameObject* test2 = new GameObject();   
            Mesh* mesh2 = new Mesh(vertices, indices, shader.GetID(), test2->transform);
            mesh2->AddTexture("test.jpg");
            test2->AddComponent(mesh2);
            test2->transform->position.y = -2;
            transformTest->AddChild(test2);

            GameObject* test3 = new GameObject();
            Mesh* mesh3 = new Mesh(vertices, indices, shader.GetID(), test3->transform);
            mesh3->AddTexture("test.jpg");
            test3->AddComponent(mesh3);
            test3->transform->position.y = 2;
            transformTest->AddChild(test3);

            AddGameObject(cameraObject);
            AddGameObject(test);
        }
};