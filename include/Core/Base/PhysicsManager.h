#include <btBulletDynamicsCommon.h>

class PhysicsManager
{
    private:
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btBroadphaseInterface* overlappingPairCache;
        btSequentialImpulseConstraintSolver* solver;

    public:
        btDiscreteDynamicsWorld* dynamicsWorld;

        PhysicsManager();
        void SetWorldGravity(float x, float y, float z);
        ~PhysicsManager();
};