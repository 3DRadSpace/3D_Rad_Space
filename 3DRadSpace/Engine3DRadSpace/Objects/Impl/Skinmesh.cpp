#include "Skinmesh.hpp"
#include "../Games/Game.hpp"
#include "Gizmos/SkinmeshGizmo.hpp"
#include "Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Reflection;

Skinmesh::Skinmesh() :
	IObject3D("Skinmesh", "..."),
	_model(nullptr)
{
}

Skinmesh::Skinmesh(
	const std::string &name,
	bool visible,
	RefModel3D model, 
	const Vector3 &pos,
	const Quaternion &rot,
	const Vector3& pivot,
	const Vector3& scale
	) : IObject3D(name, visible, visible, pos, pivot, rot, scale),
	Model(model),
	_model(nullptr)
{
}

Skinmesh::Skinmesh(
	const std::string &name,
	bool visible,
	const std::filesystem::path &path,
	const Vector3 &pos, 
	const Quaternion &rot,
	const Vector3 &pivot,
	const Vector3& scale
) :
	Skinmesh(name, visible, 0, pos, rot, pivot, scale)
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

void Skinmesh::Load()
{
	auto game = static_cast<Game*>(_game);

	if (_path != nullptr)
	{
		_model = game->Content->Load<ModelAsset>(*_path)->Get();
		_path.reset();
	}
	if (Model)
	{
		_model = const_cast<Model3D*>((*game->Content)[Model]->Get());
	}
}

void Skinmesh::Load(const std::filesystem::path& path)
{
	auto game = static_cast<Game*>(_game);
	_model = game->Content->Load<ModelAsset>(path, &Model)->Get();
}

void Skinmesh::Update()
{
}

Reflection::UUID Skinmesh::GetUUID() const noexcept
{
	// {C3A243F6-23E2-437F-AE8A-B8E8C2A6E944}
	return {0xc3a243f6, 0x23e2, 0x437f, { 0xae, 0x8a, 0xb8, 0xe8, 0xc2, 0xa6, 0xe9, 0x44 }};
}

void Skinmesh::Draw3D()
{
	auto game = static_cast<Game*>(_game);

	if(Visible && _model)
	{
		for (auto& meshPart : *_model)
		{
			if (meshPart == nullptr) continue;

			for (auto& mesh : *meshPart)
			{
				mesh->World = GetModelMatrix();
				mesh->View = game->View;
				mesh->Projection = game->Projection;

				if (HasShadows)
				{
					game->RenderingManager->Batcher.Submit(
						mesh.get(),
						Graphics::Rendering::RenderPassType::ShadowMap
					);
				}
				{
					game->RenderingManager->Batcher.Submit(
						mesh.get(),
						Transparent ? Graphics::Rendering::RenderPassType::Transparent : Graphics::Rendering::RenderPassType::Opaque
					);
				}
			}
		}
	}
}

float Skinmesh::Intersects(const Ray&r)
{
	Matrix4x4 modelMatrix = GetModelMatrix();
	float closestDistance = std::numeric_limits<float>::infinity();
	
	for (auto& mesh : *_model)
	{
		for (auto& meshPart : *mesh)
		{
			if(std::isnan(r.Intersects(meshPart->GetBoundingBox()))) continue;

			auto [vertex, index] = meshPart->CreateStagingBuffers();

			void* vertexData = nullptr;
			std::ignore = vertex->ReadData(&vertexData) / vertex->StructSize();

			void* indexData = nullptr;
			size_t numIndices = index->ReadData(&indexData) / sizeof(unsigned);

			for (size_t i = 0; i + 2 < numIndices; i += 3)
			{
				auto readVector = [&vertex, &vertexData](size_t index) -> Vector3
				{
					return *reinterpret_cast<Vector3*>((static_cast<std::byte*>(vertexData)) + (vertex->StructSize() * index));
				};
				//Assuming VS_POSITION3 is the first element.
				Vector3 t1 = Vector3::Transform(readVector(static_cast<unsigned*>(indexData)[i]), modelMatrix);
				Vector3 t2 = Vector3::Transform(readVector(static_cast<unsigned*>(indexData)[i+1]), modelMatrix);
				Vector3 t3 = Vector3::Transform(readVector(static_cast<unsigned*>(indexData)[i+2]), modelMatrix);

				Triangle tri{ t1, t2, t3 };
				
				auto dst = r.Intersects(tri);
				if(!std::isnan(dst) && dst > 0.0f && dst < closestDistance)
				{
					closestDistance = dst;
				}
			}

			vertex->EndRead();
			index->EndRead();
		}
	}
	
	return (closestDistance < std::numeric_limits<float>::infinity()) 
		? closestDistance 
		: std::numeric_limits<float>::signaling_NaN();
}

Gizmos::IGizmo* Skinmesh::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Skinmesh>(this);
}

REFL_BEGIN(Skinmesh, "Skinmesh", "3D Objects", "3D model")
	REFL_FIELD(Skinmesh, std::string, Name, "Name","Skinmesh","Object's name")
	REFL_FIELD(Skinmesh, bool, Visible, "Visible", true, "Is the object visible?")
	REFL_FIELD(Skinmesh, bool, HasShadows, "Has Shadows", true, "Does the skinmesh cast shadows?")
	REFL_FIELD(Skinmesh, bool, Transparent, "Transparent", false, "Is the skinmesh transparent?")
	REFL_FIELD(Skinmesh, RefModel3D, Model, "Model", 0, "The skinmesh model")
	REFL_FIELD(Skinmesh, Vector3, Position, "Position", Vector3::Zero(), "Object's position in world space")
	REFL_FIELD(Skinmesh, Quaternion, Rotation, "Rotation", Quaternion(), "Object's rotation")
	REFL_FIELD(Skinmesh, Vector3, RotationCenter, "Rotation Center", Vector3::Zero(), "The rotation pivot")
	REFL_FIELD(Skinmesh, Vector3, Scale, "Scale", Vector3::One(), "The skinmesh scale")
REFL_END