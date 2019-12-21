#include <Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char* filename){
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

void Texture::Draw(){
    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, textureID);
}