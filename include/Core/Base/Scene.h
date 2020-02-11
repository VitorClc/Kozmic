#include <vector>

#include <Base/GameObject.h>
#include <Components/Light.h>

#include <btBulletDynamicsCommon.h>

class Scene{
    public:
        std::vector<GLuint> shaders;
        std::vector<GameObject*> gameObjects;        
        std::vector<GameObject*> cameras;        
        GameObject* directionalLight;
        std::vector<GameObject*> pointLights;
        std::vector<btCollisionShape*> colliders;

        GameObject* activeCamera;

        void AddGameObject(GameObject* _gameObject);
        void AddCamera(GameObject* _camera);
        void AddPointLight(GameObject* _pointLight, LightComponent* _lightComponent);
        void SetDirectionalLight(GameObject* _light);

        void Start();
        void UpdatePhysics(btDiscreteDynamicsWorld* dynamicsWorld);
        void Update();
        void Render(Transform* _activeCamera);
};