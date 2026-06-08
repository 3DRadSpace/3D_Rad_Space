#include "Joint.hpp"
#include "DynamicCollider.hpp"
#include "PhysicsEngine.hpp"
#include "../../Logging/Exception.hpp"
#include <PxPhysics.h>

using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::NVPhysX;
using namespace Engine3DRadSpace::Math;

static physx::PxTransform ToPxTransform(const Vector3& pos, const Quaternion& rot)
{
	return physx::PxTransform(
		physx::PxVec3(pos.X, pos.Y, pos.Z),
		physx::PxQuat(rot.X, rot.Y, rot.Z, rot.W)
	);
}

Joint::Joint(IPhysicsEngine* physics, JointType type)
	: IJoint(physics, type)
{
}

void Joint::_createJoint()
{
	if (_joint) return;

	auto* pxPhysics = static_cast<PhysicsEngine*>(_physics)->_physics;
	auto* actor0 = _actor0 ? static_cast<DynamicCollider*>(_actor0)->_rigidbody.get() : nullptr;
	auto* actor1 = _actor1 ? static_cast<DynamicCollider*>(_actor1)->_rigidbody.get() : nullptr	;

	auto frame0 = ToPxTransform(_localFrame0Position, _localFrame0Rotation);
	auto frame1 = ToPxTransform(_localFrame1Position, _localFrame1Rotation);

	switch (_type)
	{
	case JointType::Fixed:
		_joint = PxUPtr<physx::PxJoint>(physx::PxFixedJointCreate(*pxPhysics, actor0, frame0, actor1, frame1));
		break;

	case JointType::Distance:
		_joint = PxUPtr<physx::PxJoint>(physx::PxDistanceJointCreate(*pxPhysics, actor0, frame0, actor1, frame1));
		break;

	case JointType::Spherical:
		_joint = PxUPtr<physx::PxJoint>(physx::PxSphericalJointCreate(*pxPhysics, actor0, frame0, actor1, frame1));
		break;

	case JointType::Revolute:
		_joint = PxUPtr<physx::PxJoint>(physx::PxRevoluteJointCreate(*pxPhysics, actor0, frame0, actor1, frame1));
		break;

	case JointType::Prismatic:
		_joint = PxUPtr<physx::PxJoint>(physx::PxPrismaticJointCreate(*pxPhysics, actor0, frame0, actor1, frame1));
		break;

	case JointType::D6:
		_joint = PxUPtr<physx::PxJoint>(physx::PxD6JointCreate(*pxPhysics, actor0, frame0, actor1, frame1));
		break;

	default:
		throw Logging::Exception("Unknown joint type");
	}

	if (_joint)
	{
		_joint->setBreakForce(_breakForce, _breakTorque);
	}
}

void Joint::_destroyJoint()
{
	_joint.reset();
}

void Joint::SetActors(IDynamicCollider* actor0, IDynamicCollider* actor1)
{
	_actor0 = actor0;
	_actor1 = actor1;

	if (_joint)
	{
		_destroyJoint();
		_createJoint();
	}
}

void Joint::SetLocalFrame0(const Vector3& position, const Quaternion& rotation)
{
	_localFrame0Position = position;
	_localFrame0Rotation = rotation;

	if (_joint)
	{
		auto frame = ToPxTransform(position, rotation);
		_joint->setLocalPose(physx::PxJointActorIndex::eACTOR0, frame);
	}
}

void Joint::SetLocalFrame1(const Vector3& position, const Quaternion& rotation)
{
	_localFrame1Position = position;
	_localFrame1Rotation = rotation;

	if (_joint)
	{
		auto frame = ToPxTransform(position, rotation);
		_joint->setLocalPose(physx::PxJointActorIndex::eACTOR1, frame);
	}
}

void Joint::SetBreakForce(float force, float torque)
{
	_breakForce = force;
	_breakTorque = torque;

	if (_joint)
	{
		_joint->setBreakForce(force, torque);
	}
}

void Joint::GetForce(Vector3& linear, Vector3& angular)
{
	if (!_joint) 
	{
		linear = Vector3::Zero();
		angular = Vector3::Zero();
		return;
	}

	physx::PxVec3 pxLinear, pxAngular;
	_joint->getConstraint()->getForce(pxLinear, pxAngular);

	linear = Vector3(pxLinear.x, pxLinear.y, pxLinear.z);
	angular = Vector3(pxAngular.x, pxAngular.y, pxAngular.z);
}

void Joint::SetDistanceLimit(float minDistance, float maxDistance)
{
	if (_type != JointType::Distance || !_joint) return;

	auto* distanceJoint = static_cast<physx::PxDistanceJoint*>(_joint.get());
	distanceJoint->setMinDistance(minDistance);
	distanceJoint->setMaxDistance(maxDistance);
	distanceJoint->setDistanceJointFlag(physx::PxDistanceJointFlag::eMIN_DISTANCE_ENABLED, minDistance > 0.0f);
	distanceJoint->setDistanceJointFlag(physx::PxDistanceJointFlag::eMAX_DISTANCE_ENABLED, true);
}

void Joint::SetSphericalLimit(float yAngle, float zAngle)
{
	if (_type != JointType::Spherical || !_joint) return;

	auto* sphericalJoint = static_cast<physx::PxSphericalJoint*>(_joint.get());
	physx::PxJointLimitCone limit(yAngle, zAngle);
	sphericalJoint->setLimitCone(limit);
	sphericalJoint->setSphericalJointFlag(physx::PxSphericalJointFlag::eLIMIT_ENABLED, true);
}

void Joint::SetRevoluteLimit(float lower, float upper)
{
	if (_type != JointType::Revolute || !_joint) return;

	auto* revoluteJoint = static_cast<physx::PxRevoluteJoint*>(_joint.get());
	physx::PxJointAngularLimitPair limit(lower, upper);
	revoluteJoint->setLimit(limit);
	revoluteJoint->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eLIMIT_ENABLED, true);
}

void Joint::SetRevoluteDrive(float velocity, float forceLimit, bool freespin)
{
	if (_type != JointType::Revolute || !_joint) return;

	auto* revoluteJoint = static_cast<physx::PxRevoluteJoint*>(_joint.get());
	revoluteJoint->setDriveVelocity(velocity);
	revoluteJoint->setDriveForceLimit(forceLimit);
	revoluteJoint->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eDRIVE_ENABLED, true);
	revoluteJoint->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eDRIVE_FREESPIN, freespin);
}

void Joint::SetPrismaticLimit(float lower, float upper)
{
	if (_type != JointType::Prismatic || !_joint) return;

	auto* prismaticJoint = static_cast<physx::PxPrismaticJoint*>(_joint.get());
	auto* pxPhysics = static_cast<PhysicsEngine*>(_physics)->_physics;
	physx::PxJointLinearLimitPair limit(pxPhysics->getTolerancesScale(), lower, upper);
	prismaticJoint->setLimit(limit);
	prismaticJoint->setPrismaticJointFlag(physx::PxPrismaticJointFlag::eLIMIT_ENABLED, true);
}

void Joint::SetD6Motion(int axis, int motionType)
{
	if (_type != JointType::D6 || !_joint) return;

	auto* d6Joint = static_cast<physx::PxD6Joint*>(_joint.get());

	physx::PxD6Axis::Enum pxAxis;
	switch (axis)
	{
	case 0: pxAxis = physx::PxD6Axis::eX; break;
	case 1: pxAxis = physx::PxD6Axis::eY; break;
	case 2: pxAxis = physx::PxD6Axis::eZ; break;
	case 3: pxAxis = physx::PxD6Axis::eTWIST; break;
	case 4: pxAxis = physx::PxD6Axis::eSWING1; break;
	case 5: pxAxis = physx::PxD6Axis::eSWING2; break;
	default: return;
	}

	physx::PxD6Motion::Enum pxMotion;
	switch (motionType)
	{
	case 0: pxMotion = physx::PxD6Motion::eLOCKED; break;
	case 1: pxMotion = physx::PxD6Motion::eLIMITED; break;
	case 2: pxMotion = physx::PxD6Motion::eFREE; break;
	default: return;
	}

	d6Joint->setMotion(pxAxis, pxMotion);
}

void Joint::SetD6LinearLimit(float limit)
{
	if (_type != JointType::D6 || !_joint) return;

	auto* d6Joint = static_cast<physx::PxD6Joint*>(_joint.get());
	auto* pxPhysics = static_cast<PhysicsEngine*>(_physics)->_physics;
	physx::PxJointLinearLimit linearLimit(limit);
	d6Joint->setDistanceLimit(linearLimit);
}

void Joint::SetD6TwistLimit(float lower, float upper)
{
	if (_type != JointType::D6 || !_joint) return;

	auto* d6Joint = static_cast<physx::PxD6Joint*>(_joint.get());
	physx::PxJointAngularLimitPair twistLimit(lower, upper);
	d6Joint->setTwistLimit(twistLimit);
}

void Joint::SetD6SwingLimit(float yAngle, float zAngle)
{
	if (_type != JointType::D6 || !_joint) return;

	auto* d6Joint = static_cast<physx::PxD6Joint*>(_joint.get());
	physx::PxJointLimitCone swingLimit(yAngle, zAngle);
	d6Joint->setSwingLimit(swingLimit);
}

void Joint::SetD6Drive(int driveType, float stiffness, float damping, float forceLimit, bool acceleration)
{
	if (_type != JointType::D6 || !_joint) return;

	auto* d6Joint = static_cast<physx::PxD6Joint*>(_joint.get());

	physx::PxD6Drive::Enum pxDrive;
	switch (driveType)
	{
	case 0: pxDrive = physx::PxD6Drive::eX; break;
	case 1: pxDrive = physx::PxD6Drive::eY; break;
	case 2: pxDrive = physx::PxD6Drive::eZ; break;
	case 3: pxDrive = physx::PxD6Drive::eSWING; break;
	case 4: pxDrive = physx::PxD6Drive::eTWIST; break;
	case 5: pxDrive = physx::PxD6Drive::eSLERP; break;
	default: return;
	}

	physx::PxD6JointDrive drive;
	drive.stiffness = stiffness;
	drive.damping = damping;
	drive.forceLimit = forceLimit;
	drive.flags = acceleration ? physx::PxD6JointDriveFlag::eACCELERATION : physx::PxD6JointDriveFlags(0);

	d6Joint->setDrive(pxDrive, drive);
}

void Joint::SetD6DrivePosition(const Vector3& position, const Quaternion& rotation)
{
	if (_type != JointType::D6 || !_joint) return;

	auto* d6Joint = static_cast<physx::PxD6Joint*>(_joint.get());
	auto transform = ToPxTransform(position, rotation);
	d6Joint->setDrivePosition(transform);
}

void Joint::SetD6DriveVelocity(const Vector3& linear, const Vector3& angular)
{
	if (_type != JointType::D6 || !_joint) return;

	auto* d6Joint = static_cast<physx::PxD6Joint*>(_joint.get());
	physx::PxVec3 pxLinear(linear.X, linear.Y, linear.Z);
	physx::PxVec3 pxAngular(angular.X, angular.Y, angular.Z);
	d6Joint->setDriveVelocity(pxLinear, pxAngular);
}

Joint::~Joint()
{
	_destroyJoint();
}
