#pragma once

#define GLEW_STATIC

#include <vec3.hpp>
#include <GL/glew.h>

#include <Component.h>
#include <Transform.h>

#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Vertex {
    public:
        glm::vec3 position;
        glm::vec3 color;

        Vertex(glm::vec3 _position, glm::vec3 _color){
            position = _position;
            color = _color;
        };
};

class Mesh : public Component{
    public:
        Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, GLuint shader, Transform* transform);
        void Start();
        void Update();

    private:
        GLuint shader;
        Transform* transform;

        unsigned int VAO, VBO, EBO;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
};  