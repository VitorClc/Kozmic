#pragma once

#include <vector>

#include <Component.h>
#include <Transform.h>
#include <Mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

class GameObject
{
    private:
        std::vector<Component*> components;
        std::vector<GameObject*> children;
    
    public:
        Transform* transform;
        Mesh* mesh;
       
        GameObject();

        void Start();

        void Update();

        void Render(Transform* _activeCamera);

        void SetMesh(Mesh* mesh);

        void AddComponent(Component* component);

        void AddChild(GameObject* _child);
        int ChildCount();
        
        bool LoadModel(const char* filename, GLuint shader);
        void ProcessNode(aiNode* node, const aiScene* scene, GLuint shader);
};