#define GLEW_STATIC

#include <GL/glew.h>

class Texture{
    public:
        Texture(const char* filename);
        
        void Draw();
    
    private:
        GLuint textureID;
};