#include <Mesh.h>

Mesh::Mesh(
    std::vector<Vertex> _vertices, 
    std::vector<unsigned int> _indices, 
    GLuint _shader, 
    Transform* _transform
)
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

    //NORMAL
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    
    glBindVertexArray(0);
}

void Mesh::Render()
{
    glm::mat4 transformMatrix = glm::mat4(1.0f);

    if(transform->HasParent()){
        transformMatrix = transform->GetParent()->GetMatrix() * transform->GetMatrix();
    }else{
        transformMatrix = transform->GetMatrix();
    }

    glUseProgram(shader);

    unsigned int modelLoc = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));

    GLint objectColorLoc = glGetUniformLocation( shader, "objectColor" );
    GLint lightColorLoc = glGetUniformLocation( shader, "lightColor" );
    GLint lightPosLoc = glGetUniformLocation( shader, "lightPos" );
    GLint viewPosLoc = glGetUniformLocation( shader, "viewPos" );

    glUniform3f( objectColorLoc, 1.0f, 0.5f, 0.31f );
    glUniform3f( lightColorLoc, 1.0f, 1.0f, 1.0f );
    //glUniform3f( lightPosLoc, lightPos.x, lightPos.y, lightPos.z );
    //glUniform3f( viewPosLoc, camera.GetPosition( ).x, camera.GetPosition( ).y, camera.GetPosition( ).z );

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
        glm::vec3 normal;
        
        // Positions
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].z;
        position.z = mesh->mVertices[i].y;

        // Normal
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
            
        if( mesh->mTextureCoords[0] )
        {
            uv.x = mesh->mTextureCoords[0][i].x;
            uv.y = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            uv = glm::vec2( 0.0f, 0.0f );
        }
        
        Vertex newVertex(position, uv, normal);
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

Mesh::~Mesh(){
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
}