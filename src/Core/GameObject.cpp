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
    const aiScene *scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_FlipUVs );

    ProcessNode( scene->mRootNode, scene, shader );
}

void GameObject::ProcessNode(aiNode* node, const aiScene* scene, GLuint shader){
    for ( GLuint i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        GameObject* childNode = new GameObject();
        Mesh* childMesh = new Mesh(mesh, scene, shader, transform);
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