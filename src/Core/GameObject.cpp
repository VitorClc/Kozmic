#include <GameObject.h>

GameObject::GameObject(){
    transform = new Transform();
    AddComponent(transform);

    mesh = NULL;
}

void GameObject::Start(){
    //START COMPONENTS
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Start();
    }     

    //IF HAS MESH, START IT
    if(mesh != NULL){
        mesh->Start();
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

void GameObject::Render(Transform* _activeCamera, Transform* _lightPos){
    //IF HAS MESH, RENDER IT
    if(mesh != NULL){
        mesh->Render(_activeCamera, _lightPos);
    }

    //RENDER CHILDREN MESHES
    for(unsigned int i = 0; i < children.size(); i++){
        if(children[i]->mesh != NULL){
            children[i]->mesh->Render(_activeCamera, _lightPos);
        }
    }
}

void GameObject::AddComponent(Component* component){
    components.push_back(component);
}

void GameObject::SetMesh(Mesh* _mesh){
    mesh = _mesh;
}

void GameObject::AddChild(GameObject* _child){
    children.push_back(_child);
    _child->transform->SetParent(this->transform);
}

bool GameObject::LoadModel(const char* path, GLuint shader){
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile( path, 
        aiProcess_Triangulate | 
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices);

    if(!scene){
        std::cout<<"Couldn't load model"<<std::endl;
        return false;
    }

    ProcessNode( scene->mRootNode, scene, shader );

    return true;
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
        childNode->transform->rotation = glm::vec3(nodeRot.x, nodeRot.y, nodeRot.z);
        childNode->transform->scale = glm::vec3(nodeScale.x, nodeScale.y, nodeScale.z);

        Mesh* childMesh = new Mesh(mesh, scene, shader, childNode->transform);
        childNode->SetMesh(childMesh);
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