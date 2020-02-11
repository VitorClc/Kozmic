#include <Base/PhysicsManager.h>

PhysicsManager::PhysicsManager(){
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    SetWorldGravity(0, -10, 0);
}

void PhysicsManager::SetWorldGravity(float x, float y, float z){
    dynamicsWorld->setGravity(btVector3(x, y, z));
}