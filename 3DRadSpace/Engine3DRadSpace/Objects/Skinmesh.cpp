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

Skinmesh::Skinmesh(const std::string &name, bool visible, const std::string &tag, Reflection::RefModel3D model, 
    const Math::Vector3 &pos, const Math::Quaternion &rot, const Math::Vector3 &pivot, const Math::Vector3 &scale) :
    IObject3D(name, tag, visible, visible, pos, pivot, rot, scale),
    Model(model),
    _model(nullptr)
{
}

Skinmesh::Skinmesh(const std::string &name, bool visible, const std::string &tag, const std::filesystem::path &path, const Math::Vector3 &pos,
    const Math::Quaternion &rot, const Math::Vector3 &pivot, const Math::Vector3 &scale) :
    IObject3D(name, tag, visible, visible, pos, pivot, rot, scale)
{
    _path = std::make_unique<std::string>(path.string());
}

Engine3DRadSpace::Graphics::Model3D *Engine3DRadSpace::Objects::Skinmesh::GetModel()
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

void Engine3DRadSpace::Objects::Skinmesh::Draw(Engine3DRadSpace::Math::Matrix &view, Engine3DRadSpace::Math::Matrix &projection, double dt)
{
    if(Visible)
        _model->Draw(GetModelMartix(), view, projection);
}

void Engine3DRadSpace::Objects::Skinmesh::EditorDraw(const Engine3DRadSpace::Math::Matrix &view, const Engine3DRadSpace::Math::Matrix &projection, double dt, bool selected)
{
    if(selected)
    {
        //TODO: Draw highlighted model
    }
    _model->Draw(GetModelMartix(), view, projection);
}

std::optional<float> Engine3DRadSpace::Objects::Skinmesh::Intersects(const Math::Ray &r)
{
    return std::nullopt;
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