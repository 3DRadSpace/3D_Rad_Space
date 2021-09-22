#include "Skinmesh.h"

Matrix Skinmesh::GetTranslation()
{
    return Matrix::CreateTranslation(-this->Center) * Matrix::CreateScale(this->Scale) * Matrix::CreateFromQuaternion(this->Rotation) * Matrix::CreateTranslation(this->Position);
}

void Skinmesh::Update(float dt)
{

}

void Skinmesh::Draw(float dt, Game* g)
{
    model->Draw();
}

Skinmesh::~Skinmesh()
{
    if(model != nullptr) delete model;
}
