#include "CharacterController.hpp"
#include "../../Logging/Exception.hpp"
#include <characterkinematic/PxControllerManager.h>
#include <characterkinematic/PxController.h>
#include <characterkinematic/PxCapsuleController.h>
#include <PxPhysics.h>
#include <PxScene.h>
#include <PxRigidDynamic.h>
#include <PxMaterial.h>
#include <geometry/PxGeometryQuery.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::NVPhysX;

CharacterController::CharacterController(
	IPhysicsEngine* physics,
	float height, 
	float radius,
	const Math::Vector3& position
) : ICharacterController(physics)
{
	_height = height;
	_radius = radius;
	_position = position;

	auto nvPhysics = static_cast<physx::PxPhysics*>(static_cast<PhysicsEngine*>(physics)->GetPhysics());
	auto nvControllerManager = static_cast<physx::PxControllerManager*>(static_cast<PhysicsEngine*>(physics)->_controllerManager.get());

	physx::PxCapsuleControllerDesc desc;
	desc.setToDefault();
	// position is the feet (base) of the capsule; PhysX wants the center
	desc.position = physx::PxExtendedVec3(position.X, position.Y + height / 2.0f + radius, position.Z);
	desc.height = height;
	desc.radius = radius;
	desc.contactOffset = std::max(radius * 0.1f, 0.05f); // skin to catch geometry before penetration
	desc.slopeLimit = std::cos(_maxSlopeAngle);
	desc.material = nvPhysics->createMaterial(0.5f, 0.5f, 0.0f);
	_material = PxUPtr<physx::PxMaterial>(desc.material);

	auto controller = nvControllerManager->createController(desc);
	if(controller == nullptr)
	{
		throw Logging::Exception("CharacterController creation failed!");
	}
	_controller.reset(static_cast<physx::PxCapsuleController*>(controller));

	auto scene = static_cast<physx::PxScene*>(physics->GetScene());
	auto g = scene->getGravity();
	_gravity = Vector3(g.x, g.y, g.z);
}

void CharacterController::SetHeight(float height)
{
	_height = height;
	if(_controller)
		_controller->resize(height);
}

float CharacterController::GetHeight() const
{
	if(_controller)
		return _controller->getHeight();
	return _height;
}

void CharacterController::SetRadius(float radius)
{
	_radius = radius;
	if(_controller)
		_controller->setRadius(radius);
}

float CharacterController::GetRadius() const
{
	if(_controller)
		return _controller->getRadius();
	return _radius;
}

float CharacterController::GetMaxSlopeAngle() const
{
	if(_controller)
		return std::acos(_controller->getSlopeLimit());
	return _maxSlopeAngle;
}

void CharacterController::SetMaxSlopeAngle(float angle)
{
	_maxSlopeAngle = angle;
	if(_controller)
		_controller->setSlopeLimit(std::cos(angle));
}

Math::Vector3 CharacterController::GetGravity() const
{
	return _gravity;
}

void CharacterController::SetGravity(const Math::Vector3& gravity)
{
	_gravity = gravity;
}

void CharacterController::Move(const Math::Vector3& displacement)
{
	if(!_controller) return;

	float dt = static_cast<float>(_physics->dt());

	_verticalVelocity += _gravity * dt;

	if(IsGrounded() && Vector3::Dot(_verticalVelocity, _gravity) >= 0.0f)
		_verticalVelocity = Vector3::Zero();

	physx::PxVec3 motion =
		physx::PxVec3(displacement.X, displacement.Y, displacement.Z) + (physx::PxVec3(_verticalVelocity.X, _verticalVelocity.Y, _verticalVelocity.Z) * dt);

		_controller->move(
			motion,
			0.001f,
			dt,
			physx::PxControllerFilters(),
			nullptr
		);
}

void CharacterController::Jump(float height)
{
	if(!IsGrounded() || height <= 0.0f) return;

	float g = _gravity.Length();
	if(g == 0.0f) return;

   // Conservation of energy: (1/2)m(v^2) = mgh -> v = sqrt(2gh)
	float speed = std::sqrt(2.0f * g * height);
	_verticalVelocity = Vector3::Normalize(_gravity) * -speed;
}

bool CharacterController::IsGrounded()
{
	if(_controller)
	{
		physx::PxControllerState state;
		_controller->getState(state);

		if((state.collisionFlags & physx::PxControllerCollisionFlag::eCOLLISION_UP) != 0)
		{
			_verticalVelocity = Vector3::Zero();
		}

		return (state.collisionFlags & physx::PxControllerCollisionFlag::eCOLLISION_DOWN) != 0;
	}

	return false;
}

float CharacterController::GetMass() const
{
	return 0.0f;
}

void CharacterController::SetMass(float mass)
{
	(void)mass;
}

std::optional<float> CharacterController::Intersects(const Math::Ray& r)
{
	if(_controller == nullptr) return std::nullopt;

	physx::PxVec3 origin(r.Origin.X, r.Origin.Y, r.Origin.Z);
	physx::PxVec3 dir(r.Direction.X, r.Direction.Y, r.Direction.Z);

	if(dir.normalize() == 0.0f) return std::nullopt;

	auto numShapes = _controller->getActor()->getNbShapes();
	if(numShapes == 0) return std::nullopt;

	std::vector<physx::PxShape*> shapes(numShapes);
	auto rigidbody = _controller->getActor();
	rigidbody->getShapes(shapes.data(), numShapes);

	float closestDist = PX_MAX_F32;
	bool hasHit = false;

	for(auto* shape : shapes)
	{
		physx::PxTransform pose = rigidbody->getGlobalPose() * shape->getLocalPose();
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

void CharacterController::UpdateTransform()
{
	if(!_controller) return;

	// Use foot position so _position always represents the base of the capsule,
	// consistent with how GetViewMatrix builds the eye position (Position + Height).
	auto p = _controller->getFootPosition();
	Vector3 candidate(static_cast<float>(p.x), static_cast<float>(p.y), static_cast<float>(p.z));

	auto str = std::format("CharacterController::UpdateTransform - Position: ({}, {}, {})\r\n", candidate.X, candidate.Y, candidate.Z);
	OutputDebugStringA(str.c_str());

	//if(std::isfinite(candidate.X) && std::isfinite(candidate.Y) && std::isfinite(candidate.Z))
		_position = candidate;
}

void CharacterController::UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation)
{
	if(!_controller) return;
	// position is feet; convert to capsule center for PhysX
	_controller->setPosition(physx::PxExtendedVec3(position.X, position.Y + _height / 2.0f + _radius, position.Z));

	(void)rotation;
}

Math::Vector3 CharacterController::GetPosition() const
{
	return _position;
}

void CharacterController::SetPosition(const Math::Vector3& position)
{
	_position = position; // keep cache in sync immediately
	if(!_controller) return;
	// PhysX setPosition expects the capsule center; offset from feet
	_controller->setPosition(physx::PxExtendedVec3(position.X, position.Y + _height / 2.0f + _radius, position.Z));
}

Math::Quaternion CharacterController::GetRotation() const
{
	return Math::Quaternion();
}

void CharacterController::SetRotation(const Math::Quaternion& rotation)
{
	(void)rotation;
}