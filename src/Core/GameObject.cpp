#include <GameObject.h>

GameObject::GameObject(){
    transform = new Transform();
    AddComponent(transform);
}

void GameObject::Start(){
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Start();
    }     

    //START CHILDREN
    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->Start();
    }     
}

void GameObject::Update(){
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Update();
    }

    //UPDATE CHILDREN
    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->Update();
    }
}

void GameObject::AddComponent(Component* component){
    components.push_back(component);
}

void GameObject::AddChild(GameObject* _child){
    children.push_back(_child);
    _child->transform->SetParent(this->transform);
}

void GameObject::LoadModel(const char* path, GLuint shader){
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile( path, 
        aiProcess_Triangulate | 
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices);

    ProcessNode( scene->mRootNode, scene, shader );
}

void GameObject::ProcessNode(aiNode* node, const aiScene* scene, GLuint shader){

    aiVector3t<float> nodeScale = aiVector3t<float>(0,0,0);
    aiVector3t<float> nodeRot = aiVector3t<float>(0,0,0);
    aiVector3t<float> nodePos = aiVector3t<float>(0,0,0);

    node->mTransformation.Decompose(nodeScale, nodeRot, nodePos);

    for ( GLuint i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        GameObject* childNode = new GameObject();

        //CHANGE TRANSFORM
        childNode->transform->position = glm::vec3(nodePos.x, nodePos.z, nodePos.y);
        childNode->transform->rotation = glm::vec3(nodeRot.x, nodeRot.z, nodeRot.y);
        childNode->transform->scale = glm::vec3(nodeScale.x, nodeScale.z, nodeScale.y);

        Mesh* childMesh = new Mesh(mesh, scene, shader, childNode->transform);
        childNode->AddComponent(childMesh);
        AddChild(childNode);
    }

    for ( GLuint i = 0; i < node->mNumChildren; i++ )
    {
        ProcessNode( node->mChildren[i], scene, shader);
    }
}

int GameObject::ChildCount(){
    return children.size();
}