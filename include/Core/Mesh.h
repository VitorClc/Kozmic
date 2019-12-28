#pragma once

#define GLEW_STATIC

#include <GL/glew.h>

#include <Component.h>
#include <Transform.h>

#include <vector>
#include <gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <assimp/scene.h>

class Texture{
    public:
        Texture(const char* filename){
            int width, height, numComponents;

            unsigned char* data = stbi_load(filename, &width, &height, &numComponents, 4);        

            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
                
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        
        void Draw(){
            glActiveTexture(GL_TEXTURE);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
    
    private:
        GLuint textureID;
};

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

        Mesh(
            aiMesh* _mesh,
            const aiScene* _scene,
            GLuint _shader,
            Transform* _transform
        );

        ~Mesh();

        void AddTexture(const char* filename);

        void ProcessModel(aiMesh *mesh, const aiScene *scene);

        void Start();
        void Update();

    private:
        GLuint shader;
        Transform* transform;

        unsigned int VAO, VBO, EBO, textureBuffer;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Texture* texture;
};  