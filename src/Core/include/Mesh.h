#pragma once

#define GLEW_STATIC

#include <vec3.hpp>
#include <GL/glew.h>

#include <Component.h>
#include <Transform.h>
#include <Texture.h>

#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Vertex {
    public:
        glm::vec3 position;
        glm::vec2 uv;

        Vertex(glm::vec3 _position, glm::vec2 _uv){
            position = _position;
            uv = _uv;
        };
};

class Mesh : public Component{
    public:
        Mesh(
            std::vector<Vertex> _vertices, 
            std::vector<unsigned int> _indices, 
            GLuint _shader, 
            Transform* _transform
        );

        void AddTexture(const char* filename);

        void Start();
        void Update();

    private:
        GLuint shader;
        Transform* transform;

        unsigned int VAO, VBO, EBO, textureBuffer;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        Texture* texture;
};  