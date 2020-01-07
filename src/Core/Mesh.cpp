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

    glUseProgram(shader);   
    glUniform1i( glGetUniformLocation( shader, "material.diffuseTexture" ),  0 );
    glUniform1i( glGetUniformLocation( shader, "material.specularTexture" ),  1 );
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

    glUniform3f(glGetUniformLocation(shader, "light.ambient"), 0.3f,0.3f,0.3f);
    glUniform3f(glGetUniformLocation(shader, "light.diffuse"), 0.5f,0.5f,0.5f);
    glUniform3f(glGetUniformLocation(shader, "light.specular"), 1.0f,1.0f,1.0f);
 
    if(material.hasDiffuseTexture == true){
        glUniform1i(glGetUniformLocation(shader, "material.hasDiffuseTexture"), 1);
    }else{
        glUniform1i(glGetUniformLocation(shader, "material.hasDiffuseTexture"), 0);
    }

    if(material.hasSpecularTexture == true){
        glUniform1i(glGetUniformLocation(shader, "material.hasSpecularTexture"), 1);
    }else{
        glUniform1i(glGetUniformLocation(shader, "material.hasSpecularTexture"), 0);
    }

    glUniform3f(glGetUniformLocation(shader, "material.ambient"), material.ambientColor.x, material.ambientColor.y, material.ambientColor.z);
    glUniform3f(glGetUniformLocation(shader, "material.diffuse"), material.diffuseColor.x, material.diffuseColor.y, material.diffuseColor.z);
    glUniform3f(glGetUniformLocation(shader, "material.specular"),  material.specularColor.x, material.specularColor.y, material.specularColor.z);
    glUniform1f(glGetUniformLocation(shader, "material.shininess"), 32.0f);
    
    if(material.hasDiffuseTexture == true){
        material.DrawDiffuse();
    }

    if(material.hasSpecularTexture == true){
        material.DrawSpecular();
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::ProcessModel(aiMesh *mesh, const aiScene *scene){

    aiColor4D ambientColor;
    aiColor4D diffuseColor;
    aiColor4D specularColor;
    aiString diffuseTexturePath;
    aiString specularTexturePath;
    float shininess;

    std::string texturePath;

    aiMaterial *loadedMaterial = scene->mMaterials[mesh->mMaterialIndex];

    if (loadedMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), diffuseTexturePath) == AI_SUCCESS){
        texturePath = "diffuse/";
        texturePath += diffuseTexturePath.C_Str();
        material.diffuseTexture.SetTexture(texturePath.c_str());
        material.hasDiffuseTexture = true;
    }else{material.hasDiffuseTexture = false;}

    if (loadedMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), specularTexturePath) == AI_SUCCESS){
        texturePath = "specular/";
        texturePath += specularTexturePath.C_Str();
        material.specularTexture.SetTexture(texturePath.c_str());
        material.hasSpecularTexture = true;
    }else{material.hasSpecularTexture = false;}

    if (loadedMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor) == AI_SUCCESS)
        material.ambientColor = glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b);

    if (loadedMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS){
        if(diffuseColor.r == 0 && diffuseColor.g == 0 && diffuseColor.b == 0){
            material.diffuseColor = glm::vec3(1, 1, 1);
        }else{
            material.diffuseColor = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);
        }
    }

    if (loadedMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS)
        material.specularColor = glm::vec3(specularColor.r, specularColor.g, specularColor.b);

    for ( GLuint i = 0; i < mesh->mNumVertices; i++ )
    {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
        
        // Positions
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;

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