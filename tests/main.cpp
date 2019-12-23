#define SDL_MAIN_HANDLED

#include <Shader.h>
#include <Window.h>
#include <Mesh.h>
#include <Transform.h>
#include <GameObject.h>
#include <Camera.h>

int main(){
    Window window = Window(1024,720,"TESTS");

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

    GameObject cameraObject = GameObject();
    cameraObject.transform->position.z = -3;
    Camera* cameraComponent = new Camera(shader.GetID(), cameraObject.transform);
    cameraObject.AddComponent(cameraComponent);
    cameraObject.Start();

    GameObject test = GameObject();
    Mesh* mesh = new Mesh(vertices, indices, shader.GetID(), test.transform);
    mesh->AddTexture("test.jpg");
    test.AddComponent(mesh);

    test.transform->rotation.x = 0.55;
    test.transform->scale = glm::vec3(0.5, 0.5, 0.5);

    test.Start();

    float counter = 0;

    while (window.isRunning())
    {
        window.Clear(0.24, 0.24, 0.24, 1.0);

        cameraObject.Update();

        test.transform->rotation.x = counter;
        test.transform->rotation.y = counter;

        counter += 0.01f;

        test.Update();

        window.Update();
    }

    return 0;
}