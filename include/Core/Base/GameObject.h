#pragma once

#include <vector>

#include <Base/Component.h>
#include <Components/Transform.h>
#include <Renderers/MeshRenderer.h>

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
        Renderer* renderer;
       
        GameObject();

        void Start();

        void Update();

        void Render(Transform* _activeCamera);

        void SetRenderer(Renderer* _renderer);

        void AddComponent(Component* component);

        void AddChild(GameObject* _child);
        int ChildCount();
        
        bool LoadModel(const char* filename, GLuint shader);
        void ProcessNode(aiNode* node, const aiScene* scene, GLuint shader);
};