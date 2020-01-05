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
        
        GLuint GetID(){
            return textureID;
        }
    
    private:
        GLuint textureID;
};

class Material{
    public:
        Material(){};

        glm::vec3 ambientColor = glm::vec3(0.0,0.0,0.0);
        glm::vec3 diffuseColor = glm::vec3(1.0,1.0,1.0);
        glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
        Texture diffuseTexture = Texture("diffuseTest.png");
        Texture specularTexture = Texture("specularTest.png");
        float shininess = 32.0f;

        void DrawDiffuse(){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseTexture.GetID());
        }

        void DrawSpecular(){
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularTexture.GetID());
        }
};

class Vertex {
    public:
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;

        Vertex(glm::vec3 _position, glm::vec2 _uv, glm::vec3 _normal){
            position = _position;
            uv = _uv;
            normal = _normal;
        };
};

class Mesh{
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

        void ProcessModel(aiMesh *mesh, const aiScene *scene);

        void Start();
        void Render(Transform* _activeCamera, Transform* _lightPos);

    private:
        GLuint shader;
        Transform* transform;

        unsigned int VAO, VBO, EBO, textureBuffer;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        
        Material material = Material();
};  