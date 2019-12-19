#define GLEW_STATIC

#include <vector>
#include <vec3.hpp>
#include <GL/glew.h>

class Vertex {
    public:
        glm::vec3 position;
        glm::vec3 color;

        Vertex(glm::vec3 _position, glm::vec3 _color){
            position = _position;
            color = _color;
        };
};

class Mesh {
    public:
        Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices);
        void Draw(GLuint shader);

    private:
        unsigned int VAO, VBO, EBO;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

};  