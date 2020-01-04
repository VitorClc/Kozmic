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

void Mesh::Render(Transform* _activeCamera, Transform* _lightPos)
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

    GLint lightPosLoc = glGetUniformLocation( shader, "light.position" );
    GLint viewPosLoc = glGetUniformLocation( shader, "viewPos" );

    glUniform3f(lightPosLoc,_lightPos->position.x, 
                            _lightPos->position.y, 
                            _lightPos->position.z);

    glUniform3f(viewPosLoc, _activeCamera->position.x, 
                            _activeCamera->position.y, 
                            _activeCamera->position.z);

    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

    glUniform3f(
        glGetUniformLocation(shader, "light.ambient"),
        ambientColor.x, ambientColor.g, ambientColor.b
    );

    glUniform3f(
        glGetUniformLocation(shader, "light.diffuse"),
        diffuseColor.x, diffuseColor.g, diffuseColor.b
    );

    glUniform3f(glGetUniformLocation(shader, "specular"), 1.0f, 1.0f, 1.0f);

    glUniform3f(glGetUniformLocation(shader, "material.ambient"), material.ambientColor.x, material.ambientColor.y, material.ambientColor.z);
    glUniform3f(glGetUniformLocation(shader, "material.diffuse"), material.diffuseColor.x, material.diffuseColor.y, material.diffuseColor.z);
    glUniform3f(glGetUniformLocation(shader, "material.specular"),  material.specularColor.x, material.specularColor.y, material.specularColor.z);
    glUniform1f(glGetUniformLocation(shader, "material.shininess"), material.shininess);

    if(textures.size() != 0){
        texture->Draw();    
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::ProcessModel(aiMesh *mesh, const aiScene *scene){

    aiColor4D ambientColor;
    aiColor4D diffuseColor;
    aiColor4D specularColor;
    float shininess;

    if (AI_SUCCESS == aiGetMaterialColor(scene->mMaterials[mesh->mMaterialIndex], AI_MATKEY_COLOR_AMBIENT, &ambientColor))
        material.ambientColor = glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b);

    if (AI_SUCCESS == aiGetMaterialColor(scene->mMaterials[mesh->mMaterialIndex], AI_MATKEY_COLOR_DIFFUSE, &diffuseColor))
        material.diffuseColor = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);

    if (AI_SUCCESS == aiGetMaterialColor(scene->mMaterials[mesh->mMaterialIndex], AI_MATKEY_COLOR_SPECULAR, &specularColor))
        material.specularColor = glm::vec3(specularColor.r, specularColor.g, specularColor.b);

    if (AI_SUCCESS == aiGetMaterialFloat(scene->mMaterials[mesh->mMaterialIndex], AI_MATKEY_SHININESS, &shininess))
        material.shininess = shininess; 

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
        normal.y = mesh->mNormals[i].z;
        normal.z = mesh->mNormals[i].y;
            
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