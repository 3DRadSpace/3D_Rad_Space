#include "DynamicCollider.hpp"
#include "PhysicsEngine.hpp"
#include <PxMaterial.h>
#include <extensions/PxRigidBodyExt.h>
#include <geometry/PxGeometryQuery.h>
#include <PxScene.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::NVPhysX;

DynamicCollider::DynamicCollider(IPhysicsEngine* physics) : IDynamicCollider(physics)
{
	_generateRigidbody();
}

void DynamicCollider::_generateRigidbody()
{
	auto nvPhysics = static_cast<physx::PxPhysics*>(static_cast<PhysicsEngine*>(_physics)->GetPhysics());

	if(nvPhysics == nullptr)
	{
		throw std::runtime_error("PhysX physics object is null");
	}

	auto material = nvPhysics->createMaterial(_staticFriction, _dynamicFriction, _restitution);
	_material.reset(material);

	auto p = _position;
	auto q = _rotation;

	physx::PxTransform transform{};
	transform.p = physx::PxVec3(p.X, p.Y, p.Z);
	transform.q = physx::PxQuat(-q.X, -q.Y, -q.Z, q.W);

	// Validate transform
	if(!transform.isValid())
	{
		throw std::runtime_error("Invalid transform for dynamic rigidbody creation");
	}

	auto rigidDynamic = nvPhysics->createRigidDynamic(transform);
	if(rigidDynamic == nullptr)
	{
		throw std::runtime_error("Failed to create PhysX dynamic rigidbody");
	}

	rigidDynamic->setMass(_mass);
	rigidDynamic->setLinearDamping(_linearDamping);
	rigidDynamic->setAngularDamping(_angularDamping);
	rigidDynamic->setMaxAngularVelocity(_maxAngularVelocity.X);
	rigidDynamic->setLinearVelocity(physx::PxVec3(_linearVelocity.X, _linearVelocity.Y, _linearVelocity.Z));
	rigidDynamic->setAngularVelocity(physx::PxVec3(_angularVelocity.X, _angularVelocity.Y, _angularVelocity.Z));

	// Enable CCD (Continuous Collision Detection) to prevent tunneling
	rigidDynamic->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, true);

	// Disable sleeping to ensure the rigidbody stays active
	rigidDynamic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, false);
	rigidDynamic->setSleepThreshold(0.0f);
	//rigidDynamic->wakeUp();

	_rigidbody.reset(rigidDynamic);

	auto scene = static_cast<physx::PxScene*>(_physics->GetScene());
	if(scene == nullptr)
	{
		throw std::runtime_error("PhysX scene is null");
	}

	bool success = scene->addActor(*_rigidbody);
	if(!success)
	{
		throw std::runtime_error("Failed to add dynamic rigidbody to PhysX scene");
	}
}

float DynamicCollider::GetMass() const
{
	if(_rigidbody == nullptr) return _mass;
	return static_cast<float>(_rigidbody->getMass());
}

void DynamicCollider::SetMass(float mass)
{
	if(_rigidbody) _rigidbody->setMass(mass);
	else _mass = mass;
}

float DynamicCollider::GetLinearDamping() const
{
	if(_rigidbody == nullptr) return _linearDamping;
	return _rigidbody->getLinearDamping();
}

void DynamicCollider::SetLinearDamping(float linearDamping)
{
	if(_rigidbody) _rigidbody->setLinearDamping(linearDamping);
	else _linearDamping = linearDamping;
}

float DynamicCollider::GetAngularDamping() const
{
	if(_rigidbody == nullptr) return _angularDamping;
	return _rigidbody->getAngularDamping();
}

void DynamicCollider::SetAngularDamping(float angularDamping)
{
	if(_rigidbody == nullptr) _angularDamping = angularDamping;
	else _rigidbody->setAngularDamping(angularDamping);
}

float DynamicCollider::GetStaticFriction() const
{
	if(_material) return _material->getStaticFriction();
	return _staticFriction;
}

void DynamicCollider::SetStaticFriction(float friction)
{
	if(_material) _material->setStaticFriction(friction);
	else _staticFriction = friction;
}

float DynamicCollider::GetDynamicFriction() const
{
	if(_material) return _material->getDynamicFriction();
	return _dynamicFriction;
}

void DynamicCollider::SetDynamicFriction(float friction)
{
	if(_material) _material->setDynamicFriction(friction);
	else _dynamicFriction = friction;
}

float DynamicCollider::GetRestitution() const
{
	if(_material) return _material->getRestitution();
	return _restitution;
}

void DynamicCollider::SetRestitution(float restitution)
{
	if(_material) _material->setRestitution(restitution);
	else _restitution = restitution;
}

Math::Vector3 DynamicCollider::GetLinearVelocity() const
{
	if(_rigidbody)
	{
		auto v = _rigidbody->getLinearVelocity();
		return Vector3(v.x, v.y, v.z);
	}
	return _linearVelocity;
}

void DynamicCollider::SetLinearVelocity(const Math::Vector3 &linearVelocity)
{
	if(_rigidbody)
		_rigidbody->setLinearVelocity(physx::PxVec3(linearVelocity.X, linearVelocity.Y, linearVelocity.Z));
	else
		_linearVelocity = linearVelocity;
}

Vector3 DynamicCollider::GetAngularVelocity() const
{
	if(_rigidbody)
	{
		auto av = _rigidbody->getAngularVelocity();
		return Vector3(av.x, av.y, av.z);
	}
	return _angularVelocity;
}

void DynamicCollider::SetAngularVelocity(const Math::Vector3 & angularVelocity)
{
	if(_rigidbody)
		_rigidbody->setAngularVelocity(physx::PxVec3(angularVelocity.X, angularVelocity.Y, angularVelocity.Z));
	else
		_angularVelocity = angularVelocity;
}

Vector3 DynamicCollider::GetMaxAngularVelocity() const
{
	if(_rigidbody)
	{
		auto mav = _rigidbody->getMaxAngularVelocity();
		return Vector3(mav, mav, mav);
	}
	return _maxAngularVelocity;
}

void DynamicCollider::SetMaxAngularVelocity(const Math::Vector3 & angularVelocity)
{
	if(_rigidbody) _rigidbody->setMaxAngularVelocity(angularVelocity.X);
	else _maxAngularVelocity = angularVelocity;
}

void DynamicCollider::ApplyForce(const Math::Vector3 & force)
{
	if(_rigidbody == nullptr) return;
	_rigidbody->addForce(physx::PxVec3(force.X, force.Y, force.Z));
}

void DynamicCollider::ApplyForce(const Math::Vector3 & force, const Math::Vector3 & center)
{
	if(_rigidbody == nullptr) return;

	physx::PxRigidBodyExt::addForceAtPos(
		*_rigidbody,
		physx::PxVec3(force.X, force.Y, force.Z),
		physx::PxVec3(center.X, center.Y, center.Z)
	);
}

void DynamicCollider::ApplyTorque(const Math::Vector3 & force)
{
	if(_rigidbody == nullptr) return;
	_rigidbody->addTorque(physx::PxVec3(force.X, force.Y, force.Z));
}

void DynamicCollider::ApplyAcceleration(const Math::Vector3 & acc)
{
	if(_rigidbody == nullptr) return;
	_rigidbody->addForce(physx::PxVec3(acc.X, acc.Y, acc.Z), physx::PxForceMode::eACCELERATION);
}

void DynamicCollider::ApplyAngularAcceleration(const Math::Vector3 & acc)
{
	if(_rigidbody == nullptr) return;
	_rigidbody->addTorque(physx::PxVec3(acc.X, acc.Y, acc.Z), physx::PxForceMode::eACCELERATION);
}

void DynamicCollider::UpdateTransform()
{
	if(_rigidbody == nullptr) return;

	auto tr = _rigidbody->getGlobalPose();
	_position = {tr.p.x, tr.p.y, tr.p.z};
	_rotation = {-tr.q.x, -tr.q.y, -tr.q.z, tr.q.w};
}

void DynamicCollider::UpdateTransform(const Math::Vector3 &position, const Math::Quaternion & rotation)
{
	if(_rigidbody == nullptr) return;

	_rigidbody->setGlobalPose(physx::PxTransform(
		physx::PxVec3(position.X, position.Y, position.Z),
		physx::PxQuat(-rotation.X, -rotation.Y, -rotation.Z, rotation.W)
	));
}

std::optional<float> DynamicCollider::Intersects(const Math::Ray& r)
{
	if(_rigidbody == nullptr) return std::nullopt;

	physx::PxVec3 origin(r.Origin.X, r.Origin.Y, r.Origin.Z);
	physx::PxVec3 dir(r.Direction.X, r.Direction.Y, r.Direction.Z);

	if(dir.normalize() == 0.0f) return std::nullopt;

	physx::PxU32 numShapes = _rigidbody->getNbShapes();
	if(numShapes == 0) return std::nullopt;

	std::vector<physx::PxShape*> shapes(numShapes);
	_rigidbody->getShapes(shapes.data(), numShapes);

	float closestDist = PX_MAX_F32;
	bool hasHit = false;

	for(auto* shape : shapes)
	{
		physx::PxTransform pose = _rigidbody->getGlobalPose() * shape->getLocalPose();
		physx::PxRaycastHit hit;

		physx::PxU32 hitCount = physx::PxGeometryQuery::raycast(
			origin, dir,
			shape->getGeometry(),
			pose,
			PX_MAX_F32,
			physx::PxHitFlag::eDEFAULT,
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

void DynamicCollider::AttachShape(const Math::BoundingBox & box)
{
	if(_rigidbody == nullptr) return;
	auto nvPhysics = static_cast<physx::PxPhysics*>(static_cast<PhysicsEngine*>(_physics)->GetPhysics());

	physx::PxBoxGeometry boxGeom(box.Scale.X / 2, box.Scale.Y / 2, box.Scale.Z / 2);

	auto shape = nvPhysics->createShape(boxGeom, *_material);

	// Enable simulation and scene query flags
	shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
	shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, true);

	// BoundingBox.Position is the minimum corner, so we need to offset to the center
	shape->setLocalPose(physx::PxTransform(physx::PxVec3(
		box.Position.X + (box.Scale.X / 2),
		box.Position.Y + (box.Scale.Y / 2),
		box.Position.Z + (box.Scale.Z / 2)
	)));
	_rigidbody->attachShape(*shape);
	shape->release();
}

void DynamicCollider::AttachShape(const Math::BoundingSphere & sphere)
{
	if(_rigidbody == nullptr) return;
	auto nvPhysics = static_cast<physx::PxPhysics*>(static_cast<PhysicsEngine*>(_physics)->GetPhysics());

	physx::PxSphereGeometry sphereGeom(sphere.Radius);
	auto shape = nvPhysics->createShape(sphereGeom, *_material);

	// Enable simulation and scene query flags
	shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
	shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, true);

	shape->setLocalPose(physx::PxTransform(physx::PxVec3(sphere.Center.X, sphere.Center.Y, sphere.Center.Z)));
	_rigidbody->attachShape(*shape);
	shape->release();
}

void DynamicCollider::UpdateMassAndInertia()
{
	if(_rigidbody == nullptr) return;
	if(_mass > 0.0f)
	{
		physx::PxRigidBodyExt::updateMassAndInertia(*_rigidbody, _mass);
	}
}

void DynamicCollider::SetKinematic(bool isKinematic)
{
	if(_rigidbody == nullptr) return;

	if(isKinematic)
		_rigidbody->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);
	else
		_rigidbody->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, false);
}

Vector3 DynamicCollider::GetPosition() const
{
	if(_rigidbody == nullptr) return _position;
	auto p = _rigidbody->getGlobalPose().p;
	return Vector3(p.x, p.y, p.z);
}

void DynamicCollider::SetPosition(const Vector3 &position)
{
	if(_rigidbody == nullptr) _position = position;
	else
	{
		auto tr = _rigidbody->getGlobalPose();
		tr.p = physx::PxVec3(position.X, position.Y, position.Z);
		_rigidbody->setGlobalPose(tr);
	}
}

Quaternion DynamicCollider::GetRotation() const
{
	if(_rigidbody == nullptr) return _rotation;
	auto q = _rigidbody->getGlobalPose().q;
	return Quaternion(-q.x, -q.y, -q.z, q.w);
}

void DynamicCollider::SetRotation(const Quaternion &rotation)
{
	if(_rigidbody == nullptr) _rotation = rotation;
	else
	{
		auto tr = _rigidbody->getGlobalPose();
		tr.q = physx::PxQuat(-rotation.X, -rotation.Y, -rotation.Z, rotation.W);
		_rigidbody->setGlobalPose(tr);
	}
}

void DynamicCollider::AddLinearVelocity(const Math::Vector3& v)
{
	if(_rigidbody) {
		_rigidbody->addForce(physx::PxVec3(v.X, v.Y, v.Z), physx::PxForceMode::eVELOCITY_CHANGE);
	} else {
		_linearVelocity += v;
	}
}

void DynamicCollider::AddAngularVelocity(const Math::Vector3& v)
{
	if(_rigidbody) {
		_rigidbody->addTorque(physx::PxVec3(v.X, v.Y, v.Z), physx::PxForceMode::eVELOCITY_CHANGE);
	} else {
		_angularVelocity += v;
	}
}