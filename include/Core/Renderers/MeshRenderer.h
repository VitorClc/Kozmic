#pragma once

#define GLEW_STATIC

#include <GL/glew.h>

#include <Components/Transform.h>

#include <Base/Renderer.h>

#include <Renderers/RenderUtils.h>

#include <vector>
#include <gtc/type_ptr.hpp>

#include <assimp/scene.h>

class MeshRenderer: public Renderer{
    public:
        MeshRenderer(
            std::vector<Vertex> _vertices, 
            std::vector<unsigned int> _indices, 
            GLuint _shader, 
            Transform* _transform
        );

        MeshRenderer(
            aiMesh* _mesh,
            const aiScene* _scene,
            GLuint _shader,
            Transform* _transform
        );

        ~MeshRenderer();

        void ProcessModel(aiMesh *mesh, const aiScene *scene);

        void Start();
        void Render(Transform* _activeCamera);

    private:
        GLuint shader;
        Transform* transform;

        unsigned int VAO, VBO, EBO, textureBuffer;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        
        Material material = Material();
};  