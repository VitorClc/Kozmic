#include <vector>

#include <GameObject.h>

class Scene{
    public:
        std::vector<GameObject*> gameObjects;        

        void AddGameObject(GameObject* _gameObject);

        void Start();
        void Update();
};