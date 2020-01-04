#include <vector>

#include <GameObject.h>

class Scene{
    public:
        std::vector<GameObject*> gameObjects;        
        std::vector<GameObject*> cameras;        

        GameObject* activeCamera;

        void AddGameObject(GameObject* _gameObject);
        void AddCamera(GameObject* _camera);

        void Start();
        void Update();
        void Render(Transform* _activeCamera, Transform* _lightPos);
};