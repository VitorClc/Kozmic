#include <Mesh.h>

Mesh::Mesh(
    std::vector<Vertex> _vertices, 
    std::vector<unsigned int> _indices, 
    GLuint _shader, 
    Transform* _transform
) : Component()
{
    vertices = _vertices;
    indices = _indices;

    shader = _shader;
    transform = _transform;
}

Mesh::Mesh(
    aiMesh* _mesh,
    const aiScene* _scene,
    GLuint _shader,
    Transform* _transform
){
    ProcessModel(_mesh, _scene);
    shader = _shader;
    transform = _transform;
}

void Mesh::AddTexture(const char* filename){
    texture = new Texture(filename);
}

void Mesh::Start(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //POSITION
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    //TEXTURE
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void Mesh::Update()
{
    unsigned int modelLoc = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform->GetMatrix()));

    glUseProgram(shader);

    if(textures.size() != 0){
        texture->Draw();
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::ProcessModel(aiMesh *mesh, const aiScene *scene){

    for ( GLuint i = 0; i < mesh->mNumVertices; i++ )
    {
        glm::vec3 position;
        glm::vec2 uv;
        
        // Positions
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].z;
        position.z = mesh->mVertices[i].y;

        if( mesh->mTextureCoords[0] )
        {
            uv.x = mesh->mTextureCoords[0][i].x;
            uv.y = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            uv = glm::vec2( 0.0f, 0.0f );
        }
        
        Vertex newVertex(position, uv);
        vertices.push_back( newVertex );
    }
    

    for ( GLuint i = 0; i < mesh->mNumFaces; i++ )
    {
        aiFace face = mesh->mFaces[i];
        for ( GLuint j = 0; j < face.mNumIndices; j++ )
        {
            indices.push_back( face.mIndices[j] );
        }
    }
}