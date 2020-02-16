#include <Base/GameObject.h>

GameObject::GameObject(){
    transform = new Transform();
    AddComponent(transform);

    renderer = NULL;
}

void GameObject::Start(){
    //START COMPONENTS
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Start();
    }     

    //IF HAS MESH, START IT
    if(renderer != NULL){
        renderer->Start();
    }

    //START CHILDREN
    if(children.size() > 0){
        for(unsigned int i = 0; i < children.size(); i++){
            children[i]->Start();
        }     
    }
}

void GameObject::Update(){
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Update();
    }

    //UPDATE CHILDREN
    if(children.size() > 0){
        for(unsigned int i = 0; i < children.size(); i++){
            children[i]->Update();
        }
    }
}

void GameObject::Render(Transform* _activeCamera, GLuint _activeShader){
    //IF HAS MESH, RENDER IT
    if(renderer != NULL){
        if(renderer->material.GetShader() == _activeShader){
            renderer->Render(_activeCamera);
        }
    }

    //RENDER CHILDREN MESHES
    if(children.size() > 0){
        for(unsigned int i = 0; i < children.size(); i++){
            children[i]->Render(_activeCamera, _activeShader);
        }
    }
}

void GameObject::AddComponent(Component* component){
    components.push_back(component);
}

void GameObject::SetRenderer(Renderer* _renderer){
    renderer = _renderer;
}

void GameObject::AddChild(GameObject* _child){
    children.push_back(_child);
    _child->transform->SetParent(this->transform);
}

bool GameObject::LoadModel(const char* filename){
    Assimp::Importer importer;

    std::string completePath = "resources/models/";
    completePath += filename;

    const aiScene *scene = importer.ReadFile(completePath, 
        aiProcess_Triangulate | 
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices);

    if(!scene){
        std::cout<<"Couldn't load model"<<std::endl;
        return false;
    }

    ProcessNode( scene->mRootNode, scene );

    return true;
}

void GameObject::ProcessNode(aiNode* node, const aiScene* scene){

    aiVector3t<float> nodeScale = aiVector3t<float>(0,0,0);
    aiVector3t<float> nodeRot = aiVector3t<float>(0,0,0);
    aiVector3t<float> nodePos = aiVector3t<float>(0,0,0);

    node->mTransformation.Decompose(nodeScale, nodeRot, nodePos);

    for ( GLuint i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        GameObject* childNode = new GameObject();

        //CHANGE TRANSFORM
        childNode->transform->position = glm::vec3(nodePos.x, nodePos.y, nodePos.z);
        childNode->transform->rotation = glm::vec3(nodeRot.x, nodeRot.y, nodeRot.z);
        childNode->transform->scale = glm::vec3(nodeScale.x, nodeScale.y, nodeScale.z);

        MeshRenderer* childMesh = new MeshRenderer(mesh, scene, childNode->transform);
        childNode->SetRenderer(childMesh);
        AddChild(childNode);
    }

    for ( GLuint i = 0; i < node->mNumChildren; i++ )
    {
        ProcessNode( node->mChildren[i], scene);
    }
}

int GameObject::ChildCount(){
    return children.size();
}

GameObject* GameObject::GetChild(GLuint _child){
    return children[_child];
}