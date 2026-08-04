#include "StaticMeshCollider.hpp"
#include "../../Games/Game.hpp"
#include "../../Graphics/Model3D.hpp"
#include "../../Objects/Gizmos.hpp"
#include "PhysicsEngine.hpp"
#include <geometry/PxTriangleMesh.h>
#include <geometry/PxTriangleMeshGeometry.h>
#include <PxPhysicsAPI.h>
#include "../../Content/Assets/ModelAsset.hpp"
#include "../../Logging/Warning.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::NVPhysX;

void StaticMeshCollider::_generateRigidbody()
{
	auto nvPhysics = static_cast<physx::PxPhysics*>(static_cast<PhysicsEngine*>(_physics)->GetPhysics());

	auto material = nvPhysics->createMaterial(_staticFriction, _dynamicFriction, _restitution);
	_material.reset(material);

	physx::PxTransform transform;
	transform.p = {_position.X, _position.Y, _position.Z};
	// PhysX uses column-vector quaternion rotation, match by conjugating q.
	transform.q = {-_rotation.X, -_rotation.Y, -_rotation.Z, _rotation.W};

	std::vector<physx::PxTriangleMesh*> meshes;

	physx::PxTolerancesScale toleranceScale;
	physx::PxCookingParams cookParams(toleranceScale);
	cookParams.meshPreprocessParams |= physx::PxMeshPreprocessingFlag::eWELD_VERTICES;
	cookParams.meshWeldTolerance = 0.001f;

	for(auto &mesh : *_model)
	{
		for(auto &part : *mesh.get())
		{
			auto [vertexBuffer, indexBuffer] = part->CreateStagingBuffers();
			
			void* verts;
			void* indices;

			size_t structSize = vertexBuffer->StructSize();
			std::ignore = vertexBuffer->ReadData(&verts);
			size_t numVertices = vertexBuffer->NumVertices();

			std::unique_ptr<Vector3[]> vertices = std::make_unique<Vector3[]>(numVertices);
			for(size_t i = 0; i < numVertices; i++)
			{
				//Assume VS_Position as first element of the declaration.
				vertices[i] = *reinterpret_cast<Vector3*>((static_cast<std::byte*>(verts) + (structSize * i)));
			}

			std::ignore = indexBuffer->ReadData(&indices);	
			size_t numIndices = indexBuffer->NumIndices();

			physx::PxTriangleMeshDesc meshDesc{};
			meshDesc.setToDefault();

			meshDesc.points.count = numVertices;
			meshDesc.points.data = vertices.get();
			meshDesc.points.stride = sizeof(Vector3);

			meshDesc.triangles.count = numIndices / 3;
			meshDesc.triangles.data = indices;
			meshDesc.triangles.stride = 3 * sizeof(unsigned);

			meshDesc.flags = physx::PxMeshFlag::eFLIPNORMALS;

#if _DEBUG
		   if(!PxValidateTriangleMesh(cookParams, meshDesc))
			   Logging::PrintWarning("PhysX: PxValidateTriangleMesh failed!");
#endif
			auto cookedMesh = PxCreateTriangleMesh(
				cookParams,
				meshDesc, 
				nvPhysics->getPhysicsInsertionCallback()
			);

			vertexBuffer->EndRead();
			indexBuffer->EndRead();

			if(cookedMesh != nullptr)
				meshes.push_back(cookedMesh);
			else
				Logging::PrintWarning("PhysX: PxCreateTriangleMesh failed!");
		}
	}

	auto rigidbody = nvPhysics->createRigidStatic(transform);
	_rigidbody.reset(rigidbody);

	for(auto& mesh : meshes)
	{
		auto meshgeometry = physx::PxTriangleMeshGeometry(
			mesh,
			physx::PxMeshScale(physx::PxVec3(_scale.X, _scale.Y, _scale.Z)),
			physx::PxMeshGeometryFlags(physx::PxMeshGeometryFlag::eDOUBLE_SIDED)
		);
		auto shape = nvPhysics->createShape(meshgeometry, *_material);
		_rigidbody->attachShape(*shape);
	}

	auto scene = static_cast<physx::PxScene*>(_physics->GetScene());
	bool success = scene->addActor(*_rigidbody);
	if(!success)
	{
		Logging::PrintWarning("PhysX: StaticMeshCollider::_generateRigidbody - failed to add actor to scene.");
	}
}

float StaticMeshCollider::GetMass() const
{
	return std::numeric_limits<float>::infinity();
}

void StaticMeshCollider::SetMass(float mass)
{
}

float StaticMeshCollider::GetLinearDamping() const
{
	if(_material)
		return _material->getDamping();
	return _linearDamping;
}

void StaticMeshCollider::SetLinearDamping(float linearDamping)
{
	if(_material) _material->setDamping(linearDamping);
	else _linearDamping = linearDamping;
}

float StaticMeshCollider::GetStaticFriction() const
{
	if(_material) return _material->getStaticFriction();
	return _staticFriction;
}

void StaticMeshCollider::SetStaticFriction(float friction)
{
	if(_material) _material->setStaticFriction(friction);
	else _staticFriction = friction;
}

float StaticMeshCollider::GetDynamicFriction() const
{
	if(_material) return _material->getDynamicFriction();
	return _dynamicFriction;
}

void StaticMeshCollider::SetDynamicFriction(float friction)
{
	if(_material) _material->setDynamicFriction(friction);
	else _dynamicFriction = friction;
}

float StaticMeshCollider::GetRestitution() const
{
	if(_material) return _material->getRestitution();
	return _restitution;
}

void StaticMeshCollider::SetRestitution(float restitution)
{
	if(_material) _material->setRestitution(restitution);
	else _restitution = restitution;
}

StaticMeshCollider::StaticMeshCollider(
	IPhysicsEngine* physics,
	Graphics::Model3D* model,
	const Math::Vector3 &position,
	const Math::Quaternion &rotation,
	const Math::Vector3 &scale
) : IStaticCollider(physics),
	_model(model),
	_position(position),
	_rotation(rotation),
	_scale(scale)
{
	_generateRigidbody();
}

void StaticMeshCollider::UpdateTransform()
{
}

void StaticMeshCollider::UpdateTransform(const Math::Vector3 &position, const Math::Quaternion &rotation)
{
	if(_oldPosition == position && _oldRotation == rotation) return;

	_position = position;
	_rotation = rotation;
	_oldPosition = position;
	_oldRotation = rotation;

	_rigidbody->setGlobalPose(physx::PxTransform(
		physx::PxVec3(position.X, position.Y, position.Z),
		physx::PxQuat(-rotation.X, -rotation.Y, -rotation.Z, rotation.W)
	));
}

std::optional<float> StaticMeshCollider::Intersects(const Math::Ray &r)
{
	if(_rigidbody == nullptr) return std::nullopt;

	auto* actor = static_cast<physx::PxRigidStatic*>(_rigidbody.get());

	physx::PxVec3 origin(r.Origin.X, r.Origin.Y, r.Origin.Z);
	physx::PxVec3 dir(r.Direction.X, r.Direction.Y, r.Direction.Z);

	if(dir.normalize() == 0.0f) return std::nullopt;

	physx::PxU32 numShapes = actor->getNbShapes();
	if(numShapes == 0)
	{
		Logging::PrintWarning("PhysX: StaticMeshCollider::Intersects - no shapes attached (mesh cooking may have failed).");
		return std::nullopt;
	}

	std::vector<physx::PxShape*> shapes(numShapes);
	actor->getShapes(shapes.data(), numShapes);

	float closestDist = PX_MAX_F32;
	bool hasHit = false;

	for(auto* shape : shapes)
	{
		physx::PxTransform pose = actor->getGlobalPose() * shape->getLocalPose();
		physx::PxRaycastHit hit;

		physx::PxU32 hitCount = physx::PxGeometryQuery::raycast(
			origin, dir,
			shape->getGeometry(),
			pose,
			PX_MAX_F32,
			physx::PxHitFlag::eDEFAULT | physx::PxHitFlag::eMESH_BOTH_SIDES,
			1,
			&hit
		);

		if(hitCount > 0 && hit.distance < closestDist)
		{
			closestDist = hit.distance;
			hasHit = true;
		}
	}

	return hasHit ? std::optional<float>(closestDist) : std::nullopt;
}

Vector3 StaticMeshCollider::GetPosition() const noexcept
{
	return _position;
}

void StaticMeshCollider::SetPosition(const Vector3 &position)
{
	UpdateTransform(position, _rotation);
}

Quaternion StaticMeshCollider::GetRotation() const noexcept
{
	return _rotation;
}

void StaticMeshCollider::SetRotation(const Quaternion &rotation)
{
	UpdateTransform(_position, rotation);
}