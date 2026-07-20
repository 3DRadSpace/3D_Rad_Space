#include "Joint.hpp"
#include "RigidDynamic.hpp"
#include "../../Objects/Gizmos.hpp"
#include "../../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Physics::Objects;

Physics::Objects::Joint::Joint(
	const std::string& name,
	bool enabled,
	bool visible,
	const Math::Vector3& position,
	const Math::Quaternion& rotation,
	const Math::Vector3& scale
) : IPhysicsObject(name, enabled, visible, position, rotation, scale),
	_jointType(JointType::Fixed)
{
}

void Physics::Objects::Joint::Initialize()
{
	IPhysicsObject::Initialize();
	_joint = _physics->CreateJoint(_jointType);
}

void Physics::Objects::Joint::Load()
{
	_resolveActors();
	_updateJointParameters();
}

void Physics::Objects::Joint::Load(const std::filesystem::path& path)
{
}

void Physics::Objects::Joint::Update()
{
	if (_joint && _joint->IsBroken())
	{
	}
}

void Physics::Objects::Joint::Draw3D()
{
}

float Physics::Objects::Joint::Intersects(const Math::Ray& r)
{
	return -1.0f;
}

Reflection::UUID Physics::Objects::Joint::GetUUID() const noexcept
{
	// {0A3CD916-671C-4CA0-9E09-7A5AF67EFAD8}
	return { 0xa3cd916, 0x671c, 0x4ca0, { 0x9e, 0x9, 0x7a, 0x5a, 0xf6, 0x7e, 0xfa, 0xd8 } };
}

Engine3DRadSpace::Objects::Gizmos::IGizmo* Physics::Objects::Joint::GetGizmo() const noexcept
{
	return nullptr;
}

Physics::JointType Physics::Objects::Joint::GetJointType() const noexcept
{
	return _jointType;
}

void Physics::Objects::Joint::SetJointType(Physics::JointType type)
{
	if (_jointType == type) return;

	_jointType = type;

	if (_joint)
	{
		_joint.reset();
		_joint = _physics->CreateJoint(type);
		_updateJointParameters();
	}
}

void Joint::SetActor0(Engine3DRadSpace::Objects::ObjectID actorID)
{
	_actor0ID = actorID;
	_resolveActors();
}

void Joint::SetActor1(Engine3DRadSpace::Objects::ObjectID actorID)
{
	_actor1ID = actorID;
	_resolveActors();
}

Engine3DRadSpace::Objects::ObjectID Joint::GetActor0() const noexcept
{
	return _actor0ID;
}

Engine3DRadSpace::Objects::ObjectID Joint::GetActor1() const noexcept
{
	return _actor1ID;
}

void Joint::SetLocalFrame0Position(const Math::Vector3& position)
{
	_properties->localFrame0Position = position;
	if (_joint) _joint->SetLocalFrame0(position, _properties->localFrame0Rotation);
}

Math::Vector3 Joint::GetLocalFrame0Position() const noexcept
{
	return _properties->localFrame0Position;
}

void Physics::Objects::Joint::SetLocalFrame0Rotation(const Math::Quaternion& rotation)
{
	_properties->localFrame0Rotation = rotation;
	if (_joint) _joint->SetLocalFrame0(_properties->localFrame0Position, rotation);
}

Math::Quaternion Physics::Objects::Joint::GetLocalFrame0Rotation() const noexcept
{
	return _properties->localFrame0Rotation;
}

void Physics::Objects::Joint::SetLocalFrame1Position(const Math::Vector3& position)
{
	_properties->localFrame1Position = position;
	if (_joint) _joint->SetLocalFrame1(position, _properties->localFrame1Rotation);
}

Math::Vector3 Physics::Objects::Joint::GetLocalFrame1Position() const noexcept
{
	return _properties->localFrame1Position;
}

void Physics::Objects::Joint::SetLocalFrame1Rotation(const Math::Quaternion& rotation)
{
	_properties->localFrame1Rotation = rotation;
	if (_joint) _joint->SetLocalFrame1(_properties->localFrame1Position, rotation);
}

Math::Quaternion Physics::Objects::Joint::GetLocalFrame1Rotation() const noexcept
{
	return _properties->localFrame1Rotation;
}

void Physics::Objects::Joint::SetBreakForce(float force)
{
	_properties->breakForce = force;
	if (_joint) _joint->SetBreakForce(force, _properties->breakTorque);
}

float Physics::Objects::Joint::GetBreakForce() const noexcept
{
	return _properties->breakForce;
}

void Physics::Objects::Joint::SetBreakTorque(float torque)
{
	_properties->breakTorque = torque;
	if (_joint) _joint->SetBreakForce(_properties->breakForce, torque);
}

float Physics::Objects::Joint::GetBreakTorque() const noexcept
{
	return _properties->breakTorque;
}

bool Physics::Objects::Joint::IsBroken() const noexcept
{
	return _joint ? _joint->IsBroken() : false;
}

void Physics::Objects::Joint::SetDistanceMin(float min)
{
	_properties->distanceMin = min;
	if (_joint && _jointType == JointType::Distance)
		_joint->SetDistanceLimit(min, _properties->distanceMax);
}

float Physics::Objects::Joint::GetDistanceMin() const noexcept
{
	return _properties->distanceMin;
}

void Physics::Objects::Joint::SetDistanceMax(float max)
{
	_properties->distanceMax = max;
	if (_joint && _jointType == JointType::Distance)
		_joint->SetDistanceLimit(_properties->distanceMin, max);
}

float Physics::Objects::Joint::GetDistanceMax() const noexcept
{
	return _properties->distanceMax;
}

void Physics::Objects::Joint::SetSphericalYAngle(float angle)
{
	_properties->sphericalYAngle = angle;
	if (_joint && _jointType == JointType::Spherical)
		_joint->SetSphericalLimit(angle, _properties->sphericalZAngle);
}

float Physics::Objects::Joint::GetSphericalYAngle() const noexcept
{
	return _properties->sphericalYAngle;
}

void Physics::Objects::Joint::SetSphericalZAngle(float angle)
{
	_properties->sphericalZAngle = angle;
	if (_joint && _jointType == JointType::Spherical)
		_joint->SetSphericalLimit(_properties->sphericalYAngle, angle);
}

float Physics::Objects::Joint::GetSphericalZAngle() const noexcept
{
	return _properties->sphericalZAngle;
}

void Physics::Objects::Joint::SetRevoluteLower(float lower)
{
	_properties->revoluteLower = lower;
	if (_joint && _jointType == JointType::Revolute)
		_joint->SetRevoluteLimit(lower, _properties->revoluteUpper);
}

float Physics::Objects::Joint::GetRevoluteLower() const noexcept
{
	return _properties->revoluteLower;
}

void Physics::Objects::Joint::SetRevoluteUpper(float upper)
{
	_properties->revoluteUpper = upper;
	if (_joint && _jointType == JointType::Revolute)
		_joint->SetRevoluteLimit(_properties->revoluteLower, upper);
}

float Physics::Objects::Joint::GetRevoluteUpper() const noexcept
{
	return _properties->revoluteUpper;
}

void Physics::Objects::Joint::SetRevoluteDriveVelocity(float velocity)
{
	_properties->revoluteDriveVelocity = velocity;
	if (_joint && _jointType == JointType::Revolute)
		_joint->SetRevoluteDrive(velocity, _properties->revoluteDriveForceLimit, _properties->revoluteFreespin);
}

float Physics::Objects::Joint::GetRevoluteDriveVelocity() const noexcept
{
	return _properties->revoluteDriveVelocity;
}

void Physics::Objects::Joint::SetRevoluteDriveForceLimit(float limit)
{
	_properties->revoluteDriveForceLimit = limit;
	if (_joint && _jointType == JointType::Revolute)
		_joint->SetRevoluteDrive(_properties->revoluteDriveVelocity, limit, _properties->revoluteFreespin);
}

float Physics::Objects::Joint::GetRevoluteDriveForceLimit() const noexcept
{
	return _properties->revoluteDriveForceLimit;
}

void Physics::Objects::Joint::SetRevoluteFreespin(bool freespin)
{
	_properties->revoluteFreespin = freespin;
	if (_joint && _jointType == JointType::Revolute)
		_joint->SetRevoluteDrive(_properties->revoluteDriveVelocity, _properties->revoluteDriveForceLimit, freespin);
}

bool Physics::Objects::Joint::GetRevoluteFreespin() const noexcept
{
	return _properties->revoluteFreespin;
}

void Physics::Objects::Joint::SetPrismaticLower(float lower)
{
	_properties->prismaticLower = lower;
	if (_joint && _jointType == JointType::Prismatic)
		_joint->SetPrismaticLimit(lower, _properties->prismaticUpper);
}

float Physics::Objects::Joint::GetPrismaticLower() const noexcept
{
	return _properties->prismaticLower;
}

void Physics::Objects::Joint::SetPrismaticUpper(float upper)
{
	_properties->prismaticUpper = upper;
	if (_joint && _jointType == JointType::Prismatic)
		_joint->SetPrismaticLimit(_properties->prismaticLower, upper);
}

float Physics::Objects::Joint::GetPrismaticUpper() const noexcept
{
	return _properties->prismaticUpper;
}

void Physics::Objects::Joint::SetD6MotionX(int motion)
{
	_properties->d6MotionX = motion;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Motion(0, motion);
}

int Physics::Objects::Joint::GetD6MotionX() const noexcept
{
	return _properties->d6MotionX;
}

void Physics::Objects::Joint::SetD6MotionY(int motion)
{
	_properties->d6MotionY = motion;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Motion(1, motion);
}

int Physics::Objects::Joint::GetD6MotionY() const noexcept
{
	return _properties->d6MotionY;
}

void Physics::Objects::Joint::SetD6MotionZ(int motion)
{
	_properties->d6MotionZ = motion;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Motion(2, motion);
}

int Physics::Objects::Joint::GetD6MotionZ() const noexcept
{
	return _properties->d6MotionZ;
}

void Physics::Objects::Joint::SetD6MotionTwist(int motion)
{
	_properties->d6MotionTwist = motion;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Motion(3, motion);
}

int Physics::Objects::Joint::GetD6MotionTwist() const noexcept
{
	return _properties->d6MotionTwist;
}

void Physics::Objects::Joint::SetD6MotionSwing1(int motion)
{
	_properties->d6MotionSwing1 = motion;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Motion(4, motion);
}

int Physics::Objects::Joint::GetD6MotionSwing1() const noexcept
{
	return _properties->d6MotionSwing1;
}

void Physics::Objects::Joint::SetD6MotionSwing2(int motion)
{
	_properties->d6MotionSwing2 = motion;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Motion(5, motion);
}

int Physics::Objects::Joint::GetD6MotionSwing2() const noexcept
{
	return _properties->d6MotionSwing2;
}

void Physics::Objects::Joint::SetD6LinearLimit(float limit)
{
	_properties->d6LinearLimit = limit;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6LinearLimit(limit);
}

float Physics::Objects::Joint::GetD6LinearLimit() const noexcept
{
	return _properties->d6LinearLimit;
}

void Physics::Objects::Joint::SetD6TwistLower(float lower)
{
	_properties->d6TwistLower = lower;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6TwistLimit(lower, _properties->d6TwistUpper);
}

float Physics::Objects::Joint::GetD6TwistLower() const noexcept
{
	return _properties->d6TwistLower;
}

void Physics::Objects::Joint::SetD6TwistUpper(float upper)
{
	_properties->d6TwistUpper = upper;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6TwistLimit(_properties->d6TwistLower, upper);
}

float Physics::Objects::Joint::GetD6TwistUpper() const noexcept
{
	return _properties->d6TwistUpper;
}

void Physics::Objects::Joint::SetD6SwingYAngle(float angle)
{
	_properties->d6SwingYAngle = angle;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6SwingLimit(angle, _properties->d6SwingZAngle);
}

float Physics::Objects::Joint::GetD6SwingYAngle() const noexcept
{
	return _properties->d6SwingYAngle;
}

void Physics::Objects::Joint::SetD6SwingZAngle(float angle)
{
	_properties->d6SwingZAngle = angle;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6SwingLimit(_properties->d6SwingYAngle, angle);
}

float Physics::Objects::Joint::GetD6SwingZAngle() const noexcept
{
	return _properties->d6SwingZAngle;
}

void Physics::Objects::Joint::SetD6DriveStiffness(float stiffness)
{
	_properties->d6DriveStiffness = stiffness;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Drive(5, stiffness, _properties->d6DriveDamping, _properties->d6DriveForceLimit, _properties->d6DriveAcceleration);
}

float Physics::Objects::Joint::GetD6DriveStiffness() const noexcept
{
	return _properties->d6DriveStiffness;
}

void Physics::Objects::Joint::SetD6DriveDamping(float damping)
{
	_properties->d6DriveDamping = damping;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Drive(5, _properties->d6DriveStiffness, damping, _properties->d6DriveForceLimit, _properties->d6DriveAcceleration);
}

float Physics::Objects::Joint::GetD6DriveDamping() const noexcept
{
	return _properties->d6DriveDamping;
}

void Physics::Objects::Joint::SetD6DriveForceLimit(float limit)
{
	_properties->d6DriveForceLimit = limit;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Drive(5, _properties->d6DriveStiffness, _properties->d6DriveDamping, limit, _properties->d6DriveAcceleration);
}

float Physics::Objects::Joint::GetD6DriveForceLimit() const noexcept
{
	return _properties->d6DriveForceLimit;
}

void Physics::Objects::Joint::SetD6DriveAcceleration(bool acceleration)
{
	_properties->d6DriveAcceleration = acceleration;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6Drive(5, _properties->d6DriveStiffness, _properties->d6DriveDamping, _properties->d6DriveForceLimit, acceleration);
}

bool Physics::Objects::Joint::GetD6DriveAcceleration() const noexcept
{
	return _properties->d6DriveAcceleration;
}

void Physics::Objects::Joint::SetD6DrivePosition(const Math::Vector3& position)
{
	_properties->d6DrivePosition = position;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6DrivePosition(position, _properties->d6DriveRotation);
}

Math::Vector3 Physics::Objects::Joint::GetD6DrivePosition() const noexcept
{
	return _properties->d6DrivePosition;
}

void Physics::Objects::Joint::SetD6DriveRotation(const Math::Quaternion& rotation)
{
	_properties->d6DriveRotation = rotation;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6DrivePosition(_properties->d6DrivePosition, rotation);
}

Math::Quaternion Physics::Objects::Joint::GetD6DriveRotation() const noexcept
{
	return _properties->d6DriveRotation;
}

void Physics::Objects::Joint::SetD6DriveLinearVelocity(const Math::Vector3& velocity)
{
	_properties->d6DriveLinearVelocity = velocity;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6DriveVelocity(velocity, _properties->d6DriveAngularVelocity);
}

Math::Vector3 Physics::Objects::Joint::GetD6DriveLinearVelocity() const noexcept
{
	return _properties->d6DriveLinearVelocity;
}

void Physics::Objects::Joint::SetD6DriveAngularVelocity(const Math::Vector3& velocity)
{
	_properties->d6DriveAngularVelocity = velocity;
	if (_joint && _jointType == JointType::D6)
		_joint->SetD6DriveVelocity(_properties->d6DriveLinearVelocity, velocity);
}

Math::Vector3 Physics::Objects::Joint::GetD6DriveAngularVelocity() const noexcept
{
	return _properties->d6DriveAngularVelocity;
}

Physics::IJoint* Physics::Objects::Joint::GetJoint() const noexcept
{
	return _joint.get();
}

void Physics::Objects::Joint::_updateJointParameters()
{
	if (!_joint) return;

	_joint->SetLocalFrame0(_properties->localFrame0Position, _properties->localFrame0Rotation);
	_joint->SetLocalFrame1(_properties->localFrame1Position, _properties->localFrame1Rotation);
	_joint->SetBreakForce(_properties->breakForce, _properties->breakTorque);

	switch (_jointType)
	{
	case JointType::Distance:
		_joint->SetDistanceLimit(_properties->distanceMin, _properties->distanceMax);
		break;

	case JointType::Spherical:
		_joint->SetSphericalLimit(_properties->sphericalYAngle, _properties->sphericalZAngle);
		break;

	case JointType::Revolute:
		_joint->SetRevoluteLimit(_properties->revoluteLower, _properties->revoluteUpper);
		_joint->SetRevoluteDrive(_properties->revoluteDriveVelocity, _properties->revoluteDriveForceLimit, _properties->revoluteFreespin);
		break;

	case JointType::Prismatic:
		_joint->SetPrismaticLimit(_properties->prismaticLower, _properties->prismaticUpper);
		break;

	case JointType::D6:
		_joint->SetD6Motion(0, _properties->d6MotionX);
		_joint->SetD6Motion(1, _properties->d6MotionY);
		_joint->SetD6Motion(2, _properties->d6MotionZ);
		_joint->SetD6Motion(3, _properties->d6MotionTwist);
		_joint->SetD6Motion(4, _properties->d6MotionSwing1);
		_joint->SetD6Motion(5, _properties->d6MotionSwing2);
		_joint->SetD6LinearLimit(_properties->d6LinearLimit);
		_joint->SetD6TwistLimit(_properties->d6TwistLower, _properties->d6TwistUpper);
		_joint->SetD6SwingLimit(_properties->d6SwingYAngle, _properties->d6SwingZAngle);
		_joint->SetD6Drive(5, _properties->d6DriveStiffness, _properties->d6DriveDamping, _properties->d6DriveForceLimit, _properties->d6DriveAcceleration);
		_joint->SetD6DrivePosition(_properties->d6DrivePosition, _properties->d6DriveRotation);
		_joint->SetD6DriveVelocity(_properties->d6DriveLinearVelocity, _properties->d6DriveAngularVelocity);
		break;

	default:
		break;
	}
}

void Physics::Objects::Joint::_resolveActors()
{
	if (!_joint) return;

	_actor0Obj = nullptr;
	_actor1Obj = nullptr;
}

static int joint_getjointtype(Physics::Objects::Joint& j) { return static_cast<int>(j.GetJointType()); }
static void joint_setjointtype(Physics::Objects::Joint& j, const int& type) { j.SetJointType(static_cast<Physics::JointType>(type)); }

static Engine3DRadSpace::Objects::ObjectID joint_getactor0(Physics::Objects::Joint& j) { return j.GetActor0(); }
static void joint_setactor0(Physics::Objects::Joint& j, const Engine3DRadSpace::Objects::ObjectID& id) { j.SetActor0(id); }

static Engine3DRadSpace::Objects::ObjectID joint_getactor1(Physics::Objects::Joint& j) { return j.GetActor1(); }
static void joint_setactor1(Physics::Objects::Joint& j, const Engine3DRadSpace::Objects::ObjectID& id) { j.SetActor1(id); }

static Math::Vector3 joint_getlocalframe0pos(Physics::Objects::Joint& j) { return j.GetLocalFrame0Position(); }
static void joint_setlocalframe0pos(Physics::Objects::Joint& j, const Math::Vector3& pos) { j.SetLocalFrame0Position(pos); }

static Math::Quaternion joint_getlocalframe0rot(Physics::Objects::Joint& j) { return j.GetLocalFrame0Rotation(); }
static void joint_setlocalframe0rot(Physics::Objects::Joint& j, const Math::Quaternion& rot) { j.SetLocalFrame0Rotation(rot); }

static Math::Vector3 joint_getlocalframe1pos(Physics::Objects::Joint& j) { return j.GetLocalFrame1Position(); }
static void joint_setlocalframe1pos(Physics::Objects::Joint& j, const Math::Vector3& pos) { j.SetLocalFrame1Position(pos); }

static Math::Quaternion joint_getlocalframe1rot(Physics::Objects::Joint& j) { return j.GetLocalFrame1Rotation(); }
static void joint_setlocalframe1rot(Physics::Objects::Joint& j, const Math::Quaternion& rot) { j.SetLocalFrame1Rotation(rot); }

static float joint_getbreakforce(Physics::Objects::Joint& j) { return j.GetBreakForce(); }
static void joint_setbreakforce(Physics::Objects::Joint& j, const float& force) { j.SetBreakForce(force); }

static float joint_getbreaktorque(Physics::Objects::Joint& j) { return j.GetBreakTorque(); }
static void joint_setbreaktorque(Physics::Objects::Joint& j, const float& torque) { j.SetBreakTorque(torque); }

REFL_BEGIN(Joint, "Joint", "Physics", "A joint constraint connecting two physics actors")
REFL_FIELD(Joint, std::string, Name, "Name", "Joint", "Name of the joint")
REFL_FIELD(Joint, bool, Enabled, "Enabled", true, "Is the joint active?")
REFL_FIELD_GS(Joint, int, joint_getjointtype, joint_setjointtype, "Joint Type", 0, "Type of joint (0=Fixed, 1=Distance, 2=Spherical, 3=Revolute, 4=Prismatic, 5=D6)")
REFL_FIELD_GS(Joint, Engine3DRadSpace::Objects::ObjectID, joint_getactor0, joint_setactor0, "Actor 0", 0, "ID of the first actor")
REFL_FIELD_GS(Joint, Engine3DRadSpace::Objects::ObjectID, joint_getactor1, joint_setactor1, "Actor 1", 0, "ID of the second actor")
REFL_FIELD_GS(Joint, Math::Vector3, joint_getlocalframe0pos, joint_setlocalframe0pos, "Frame 0 Position", Math::Vector3::Zero(), "Local frame position for actor 0")
REFL_FIELD_GS(Joint, Math::Quaternion, joint_getlocalframe0rot, joint_setlocalframe0rot, "Frame 0 Rotation", Math::Quaternion(), "Local frame rotation for actor 0")
REFL_FIELD_GS(Joint, Math::Vector3, joint_getlocalframe1pos, joint_setlocalframe1pos, "Frame 1 Position", Math::Vector3::Zero(), "Local frame position for actor 1")
REFL_FIELD_GS(Joint, Math::Quaternion, joint_getlocalframe1rot, joint_setlocalframe1rot, "Frame 1 Rotation", Math::Quaternion(), "Local frame rotation for actor 1")
REFL_FIELD_GS(Joint, float, joint_getbreakforce, joint_setbreakforce, "Break Force", 3.402823466e+38f, "Maximum force before joint breaks")
REFL_FIELD_GS(Joint, float, joint_getbreaktorque, joint_setbreaktorque, "Break Torque", 3.402823466e+38f, "Maximum torque before joint breaks")
REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/Joint.html")
REFL_END
