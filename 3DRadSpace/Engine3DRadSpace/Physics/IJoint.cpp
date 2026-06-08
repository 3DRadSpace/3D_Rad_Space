#include "IJoint.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Physics;

IJoint::IJoint(IPhysicsEngine* physics, JointType type)
	: _physics(physics), _type(type), _actor0(nullptr), _actor1(nullptr),
	  _localFrame0Position(Math::Vector3::Zero()), _localFrame0Rotation(Math::Quaternion()),
	  _localFrame1Position(Math::Vector3::Zero()), _localFrame1Rotation(Math::Quaternion()),
	  _breakForce(std::numeric_limits<float>::max()), _breakTorque(std::numeric_limits<float>::max()),
	  _isBroken(false)
{
}

JointType IJoint::GetType() const noexcept
{
	return _type;
}

IDynamicCollider* IJoint::GetActor0() const noexcept
{
	return _actor0;
}

IDynamicCollider* IJoint::GetActor1() const noexcept
{
	return _actor1;
}

Math::Vector3 IJoint::GetLocalFrame0Position() const noexcept
{
	return _localFrame0Position;
}

Math::Quaternion IJoint::GetLocalFrame0Rotation() const noexcept
{
	return _localFrame0Rotation;
}

Math::Vector3 IJoint::GetLocalFrame1Position() const noexcept
{
	return _localFrame1Position;
}

Math::Quaternion IJoint::GetLocalFrame1Rotation() const noexcept
{
	return _localFrame1Rotation;
}

float IJoint::GetBreakForce() const noexcept
{
	return _breakForce;
}

float IJoint::GetBreakTorque() const noexcept
{
	return _breakTorque;
}

bool IJoint::IsBroken() const noexcept
{
	return _isBroken;
}
