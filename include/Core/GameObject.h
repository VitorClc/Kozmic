#pragma once

#include <vector>

#include <Component.h>
#include <Transform.h>
#include <Mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class GameObject
{
    private:
        std::vector<Component*> components;
        std::vector<GameObject*> children;
    
    public:
        Transform* transform;
        
        GameObject();

        void Start();

        void Update();

        void AddComponent(Component* component);

        void AddChild(GameObject* _child);
        int ChildCount();
        
        void LoadModel(const char* path, GLuint shader);
        void ProcessNode(aiNode* node, const aiScene* scene, GLuint shader);
};