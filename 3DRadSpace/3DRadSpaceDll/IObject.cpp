#include "IObject.h"

/*
* Standard matrix transform
* 
Matrix IObject::GetTranslation()
{
    return Matrix::CreateTranslation(-this->Center) * Matrix::CreateScale(this->Scale) * Matrix::CreateFromQuaternion(this->Rotation) * Matrix::CreateTranslation(this->Position);
}
*/

IObject::~IObject()
{
}
