#define STB_IMAGE_IMPLEMENTATION

#include <Base/stb_image.h>
#include <Base/Shader.h>
#include <Base/ShaderManager.h>

class Texture{
    public:
        Texture(){
        }

        Texture(const char* filename){
            SetTexture(filename);
        }
        
        void SetTexture(const char* filename){
            int width, height, numComponents;

            std::string completePath = "resources/textures/";
            completePath += filename;

            unsigned char* data = stbi_load(completePath.c_str(), &width, &height, &numComponents, 4);        

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
        Material(){ 
            shaderID = shaderManager.GetShader(0);
        };

        glm::vec3 ambientColor = glm::vec3(0.0,0.0,0.0);
        glm::vec3 diffuseColor = glm::vec3(1.0,0.0,0.0);
        glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
        Texture diffuseTexture = Texture();
        Texture specularTexture = Texture();
        float shininess = 32.0f;

        void DrawDiffuse(){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseTexture.GetID());
        }

        void DrawSpecular(){
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularTexture.GetID());
        }

        void SetShader(GLuint _newShader){
            shaderID = shaderManager.GetShader(_newShader);
        }

        bool hasDiffuseTexture = false;
        bool hasSpecularTexture = false;

        int GetShader(){
            return shaderID;
        };
    
    private:
        GLuint shaderID;
        ShaderManager& shaderManager = ShaderManager::getInstance();

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