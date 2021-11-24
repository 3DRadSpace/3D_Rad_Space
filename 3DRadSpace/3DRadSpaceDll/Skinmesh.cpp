#include "Skinmesh.h"

Engine3DRadSpace::Matrix Engine3DRadSpace::Skinmesh::GetTranslation()
{
    return Matrix::CreateTranslation(-this->Center) * Matrix::CreateScale(this->Scale) * Matrix::CreateFromQuaternion(this->Rotation) * Matrix::CreateTranslation(this->Position);
}

void Engine3DRadSpace::Skinmesh::Update(float dt)
{

}

void Engine3DRadSpace::Skinmesh::Draw(float dt, Game* g)
{
    model->Draw();
}

Engine3DRadSpace::Skinmesh::~Skinmesh()
{
    if(model != nullptr) delete model;

    this->model = nullptr;
}
