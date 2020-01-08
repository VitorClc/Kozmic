#include <vector>

#include <GameObject.h>
#include <Light.h>

class Scene{
    public:
        std::vector<GLuint> shaders;
        std::vector<GameObject*> gameObjects;        
        std::vector<GameObject*> cameras;        
        std::vector<GameObject*> directionalLights;
        std::vector<GameObject*> pointLights;

        GameObject* activeCamera;

        void AddGameObject(GameObject* _gameObject);
        void AddCamera(GameObject* _camera);
        void AddPointLight(GameObject* _pointLight, LightComponent* _lightComponent);

        void Start();
        void Update();
        void Render(Transform* _activeCamera);
};