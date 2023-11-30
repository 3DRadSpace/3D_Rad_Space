#include "Skinmesh.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Reflection;

Skinmesh::Skinmesh() :
    IObject3D("Skinmesh", "..."),
    _model(nullptr)
{
}

Skinmesh::Skinmesh(const std::string &name, bool visible, const std::string &tag, RefModel3D model, 
    const Vector3&pos, const Quaternion&rot, const Vector3&pivot, const Vector3&scale) :
    IObject3D(name, tag, visible, visible, pos, pivot, rot, scale),
    Model(model),
    _model(nullptr)
{
}

Skinmesh::Skinmesh(const std::string &name, bool visible, const std::string &tag, const std::filesystem::path &path, const
                   Vector3&pos, const Quaternion&rot, const Vector3&pivot, const Vector3&scale) :
    IObject3D(name, tag, visible, visible, pos, pivot, rot, scale),
    _model(nullptr)
{
    _path = std::make_unique<std::string>(path.string());
}

Model3D* Skinmesh::GetModel()
{
    return _model;
}

void Skinmesh::Initialize()
{
}

void Skinmesh::Load(Content::ContentManager *content)
{
    if (_path != nullptr)
    {
        _model = content->Load<Model3D>(*_path);
        _path.reset();
    }
    if (_model == nullptr && Model)
    {
        _model = static_cast<Model3D*>((*content)[Model]->Get());
    }
}

void Skinmesh::Update(Input::Keyboard &keyboard, Input::Mouse &mouse, double dt)
{
}

void Skinmesh::EditorInitialize()
{
}

void Skinmesh::EditorLoad(Content::ContentManager *content)
{
    Load(content);
}

Reflection::UUID Skinmesh::GetUUID()
{
    // {C3A243F6-23E2-437F-AE8A-B8E8C2A6E944}
    return {0xc3a243f6, 0x23e2, 0x437f, { 0xae, 0x8a, 0xb8, 0xe8, 0xc2, 0xa6, 0xe9, 0x44 }};
}

void Skinmesh::Draw(Matrix4x4&view, Matrix4x4&projection, double dt)
{
    if(Visible)
        _model->Draw(GetModelMartix(), view, projection);
}

void Skinmesh::EditorDraw(const Matrix4x4&view, const Matrix4x4&projection, double dt, bool selected)
{
    if(selected)
    {
        //TODO: Draw highlighted model
    }
    _model->Draw(GetModelMartix(), view, projection);
}

std::optional<float> Skinmesh::Intersects(const Ray&r)
{
    for (auto& mesh : *_model)
    {
        for (auto& meshPart : *mesh)
        {
            void* vertexData = nullptr;
            size_t numVerts = meshPart->VertexBuffer->ReadData(&vertexData);

            void* indexData = nullptr;
            size_t numIndices = meshPart->IndexBuffer->ReadData(&indexData);

            for (size_t i = 0; i < numIndices; i += 3)
            {
                auto readVector = [&meshPart, &vertexData](size_t index) -> Vector3
                {
                    return *reinterpret_cast<Vector3*>((static_cast<std::byte*>(vertexData)) + (meshPart->VertexBuffer->StructSize() * index));
                };
                //Assuming VS_POSITION3 is the first element.
                Vector3 t1 = readVector(i);
                Vector3 t2 = readVector(i+1);
                Vector3 t3 = readVector(i+3);

                Triangle tri{ t1, t2, t3 };
                
                auto dst = r.Intersects(tri);
                if (dst.has_value()) return dst;
            }

            meshPart->VertexBuffer->EndRead();
            meshPart->IndexBuffer->EndRead();
        }
    }
    return false;
}

REFL_BEGIN(Skinmesh, "Skinmesh", "3D Objects", "3D model")
REFL_FIELD(Skinmesh, std::string, Name, "Name","Skinmesh","Object's name")
REFL_FIELD(Skinmesh, bool, Visible, "Visible", true, "Is the object visible?")
REFL_FIELD(Skinmesh, RefModel3D, Model, "Model", 0, "The skinmesh model")
REFL_FIELD(Skinmesh, Vector3, Position, "Position", Vector3::Zero(), "Object's position in world space")
REFL_FIELD(Skinmesh, Quaternion, Rotation, "Rotation", Quaternion(), "Object's rotation")
REFL_FIELD(Skinmesh, Vector3, RotationCenter, "Rotation Center", Vector3::Zero(), "The rotation pivot")
REFL_FIELD(Skinmesh, Vector3, Scale, "Scale", Vector3::One(), "The skinmesh scale")
REFL_END