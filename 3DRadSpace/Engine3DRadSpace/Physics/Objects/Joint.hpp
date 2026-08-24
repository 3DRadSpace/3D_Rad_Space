#pragma once
#include "IPhysicsObject.hpp"
#include "../IJoint.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// A physics object representing a joint constraint between two actors.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT Joint : public IPhysicsObject
	{
	protected:
		std::unique_ptr<IJoint> _joint;

		JointType _jointType;

		struct JointProperties
		{
			Math::Vector3 localFrame0Position = Math::Vector3::Zero();
			Math::Quaternion localFrame0Rotation = Math::Quaternion();
			Math::Vector3 localFrame1Position = Math::Vector3::Zero();
			Math::Quaternion localFrame1Rotation = Math::Quaternion();

			float breakForce = std::numeric_limits<float>::max();
			float breakTorque = std::numeric_limits<float>::max();

			float distanceMin = 0.0f;
			float distanceMax = 1.0f;

			float sphericalYAngle = 1.57f;
			float sphericalZAngle = 1.57f;

			float revoluteLower = -1.57f;
			float revoluteUpper = 1.57f;
			float revoluteDriveVelocity = 0.0f;
			float revoluteDriveForceLimit = 1000.0f;
			bool revoluteFreespin = false;

			float prismaticLower = -1.0f;
			float prismaticUpper = 1.0f;

			int d6MotionX = 0;
			int d6MotionY = 0;
			int d6MotionZ = 0;
			int d6MotionTwist = 0;
			int d6MotionSwing1 = 0;
			int d6MotionSwing2 = 0;

			float d6LinearLimit = 1.0f;
			float d6TwistLower = -1.57f;
			float d6TwistUpper = 1.57f;
			float d6SwingYAngle = 1.57f;
			float d6SwingZAngle = 1.57f;

			float d6DriveStiffness = 0.0f;
			float d6DriveDamping = 0.0f;
			float d6DriveForceLimit = 1000.0f;
			bool d6DriveAcceleration = true;

			Math::Vector3 d6DrivePosition = Math::Vector3::Zero();
			Math::Quaternion d6DriveRotation = Math::Quaternion();
			Math::Vector3 d6DriveLinearVelocity = Math::Vector3::Zero();
			Math::Vector3 d6DriveAngularVelocity = Math::Vector3::Zero();
		};

		std::unique_ptr<JointProperties> _properties = std::make_unique<JointProperties>();

		Engine3DRadSpace::Objects::ObjectID _actor0ID;
		Engine3DRadSpace::Objects::ObjectID _actor1ID;

		IPhysicsObject* _actor0Obj = nullptr;
		IPhysicsObject* _actor1Obj = nullptr;

	public:
		/// <summary>
		/// Constructs a joint object.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="enabled">Is this object enabled?</param>
		/// <param name="visible">Is this object visible?</param>
		/// <param name="position">Position of the joint</param>
		/// <param name="rotation">Rotation of the joint</param>
		/// <param name="scale">Scale of the joint</param>
		explicit Joint(
			const std::string& name = "Joint",
			bool enabled = true,
			bool visible = false,
			const Math::Vector3& position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3::One()
		);

		Joint(Joint&&) noexcept = default;
		Joint& operator=(Joint&&) noexcept = default;

		/// <summary>
		/// Resolves the referenced actors and creates the underlying joint.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="path">Ignored.</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Does nothing, as joints are not rendered visually.
		/// </summary>
		void Draw3D() override;

		float Intersects(const Math::Ray& r) const override;
		/// <summary>
		/// Gets the UUID of the Joint type.
		/// </summary>
		/// <returns>{0A3CD916-671C-4CA0-9E09-7A5AF67EFAD8}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Returns null.
		/// </summary>
		/// <returns>null gizmo</returns>
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		/// <summary>
		/// Gets the type of the underlying joint (Fixed, Distance, Spherical, Revolute, Prismatic or D6).
		/// </summary>
		/// <returns>Joint type</returns>
		JointType GetJointType() const noexcept;
		/// <summary>
		/// Sets the type of the underlying joint, recreating it if it already exists.
		/// </summary>
		/// <param name="type">Joint type</param>
		void SetJointType(JointType type);

		/// <summary>
		/// Sets the first actor connected by this joint.
		/// </summary>
		/// <param name="actorID">Object identifier of a dynamic collider</param>
		void SetActor0(Engine3DRadSpace::Objects::ObjectID actorID);
		/// <summary>
		/// Sets the second actor connected by this joint.
		/// </summary>
		/// <param name="actorID">Object identifier of a dynamic collider</param>
		void SetActor1(Engine3DRadSpace::Objects::ObjectID actorID);

		/// <summary>
		/// Gets the object identifier of the first actor connected by this joint.
		/// </summary>
		/// <returns>Object identifier</returns>
		Engine3DRadSpace::Objects::ObjectID GetActor0() const noexcept;
		/// <summary>
		/// Gets the object identifier of the second actor connected by this joint.
		/// </summary>
		/// <returns>Object identifier</returns>
		Engine3DRadSpace::Objects::ObjectID GetActor1() const noexcept;

		/// <summary>
		/// Sets the local position of the joint frame attached to the first actor.
		/// </summary>
		/// <param name="position">Local frame position</param>
		void SetLocalFrame0Position(const Math::Vector3& position);
		/// <summary>
		/// Gets the local position of the joint frame attached to the first actor.
		/// </summary>
		/// <returns>Local frame position</returns>
		Math::Vector3 GetLocalFrame0Position() const noexcept;

		/// <summary>
		/// Sets the local rotation of the joint frame attached to the first actor.
		/// </summary>
		/// <param name="rotation">Local frame rotation</param>
		void SetLocalFrame0Rotation(const Math::Quaternion& rotation);
		/// <summary>
		/// Gets the local rotation of the joint frame attached to the first actor.
		/// </summary>
		/// <returns>Local frame rotation</returns>
		Math::Quaternion GetLocalFrame0Rotation() const noexcept;

		/// <summary>
		/// Sets the local position of the joint frame attached to the second actor.
		/// </summary>
		/// <param name="position">Local frame position</param>
		void SetLocalFrame1Position(const Math::Vector3& position);
		/// <summary>
		/// Gets the local position of the joint frame attached to the second actor.
		/// </summary>
		/// <returns>Local frame position</returns>
		Math::Vector3 GetLocalFrame1Position() const noexcept;

		/// <summary>
		/// Sets the local rotation of the joint frame attached to the second actor.
		/// </summary>
		/// <param name="rotation">Local frame rotation</param>
		void SetLocalFrame1Rotation(const Math::Quaternion& rotation);
		/// <summary>
		/// Gets the local rotation of the joint frame attached to the second actor.
		/// </summary>
		/// <returns>Local frame rotation</returns>
		Math::Quaternion GetLocalFrame1Rotation() const noexcept;

		/// <summary>
		/// Sets the maximum force the joint can withstand before breaking. Default is the maximum representable float value.
		/// </summary>
		/// <param name="force">Break force</param>
		void SetBreakForce(float force);
		/// <summary>
		/// Gets the maximum force the joint can withstand before breaking.
		/// </summary>
		/// <returns>Break force</returns>
		float GetBreakForce() const noexcept;

		/// <summary>
		/// Sets the maximum torque the joint can withstand before breaking. Default is the maximum representable float value.
		/// </summary>
		/// <param name="torque">Break torque</param>
		void SetBreakTorque(float torque);
		/// <summary>
		/// Gets the maximum torque the joint can withstand before breaking.
		/// </summary>
		/// <returns>Break torque</returns>
		float GetBreakTorque() const noexcept;

		/// <summary>
		/// Gets whether the joint has broken due to exceeding its break force/torque limits.
		/// </summary>
		/// <returns>True if broken, false otherwise</returns>
		bool IsBroken() const noexcept;

		/// <summary>
		/// Sets the minimum allowed distance for a Distance joint. Only applies when the joint type is Distance.
		/// </summary>
		/// <param name="min">Minimum distance</param>
		void SetDistanceMin(float min);
		/// <summary>
		/// Gets the minimum allowed distance for a Distance joint.
		/// </summary>
		/// <returns>Minimum distance</returns>
		float GetDistanceMin() const noexcept;

		/// <summary>
		/// Sets the maximum allowed distance for a Distance joint. Only applies when the joint type is Distance.
		/// </summary>
		/// <param name="max">Maximum distance</param>
		void SetDistanceMax(float max);
		/// <summary>
		/// Gets the maximum allowed distance for a Distance joint.
		/// </summary>
		/// <returns>Maximum distance</returns>
		float GetDistanceMax() const noexcept;

		/// <summary>
		/// Sets the Y angle, in radians, of the limit cone for a Spherical joint. Only applies when the joint type is Spherical.
		/// </summary>
		/// <param name="angle">Y angle, in radians</param>
		void SetSphericalYAngle(float angle);
		/// <summary>
		/// Gets the Y angle, in radians, of the limit cone for a Spherical joint.
		/// </summary>
		/// <returns>Y angle, in radians</returns>
		float GetSphericalYAngle() const noexcept;

		/// <summary>
		/// Sets the Z angle, in radians, of the limit cone for a Spherical joint. Only applies when the joint type is Spherical.
		/// </summary>
		/// <param name="angle">Z angle, in radians</param>
		void SetSphericalZAngle(float angle);
		/// <summary>
		/// Gets the Z angle, in radians, of the limit cone for a Spherical joint.
		/// </summary>
		/// <returns>Z angle, in radians</returns>
		float GetSphericalZAngle() const noexcept;

		/// <summary>
		/// Sets the lower angular limit, in radians, for a Revolute joint. Only applies when the joint type is Revolute.
		/// </summary>
		/// <param name="lower">Lower angular limit, in radians</param>
		void SetRevoluteLower(float lower);
		/// <summary>
		/// Gets the lower angular limit, in radians, for a Revolute joint.
		/// </summary>
		/// <returns>Lower angular limit, in radians</returns>
		float GetRevoluteLower() const noexcept;

		/// <summary>
		/// Sets the upper angular limit, in radians, for a Revolute joint. Only applies when the joint type is Revolute.
		/// </summary>
		/// <param name="upper">Upper angular limit, in radians</param>
		void SetRevoluteUpper(float upper);
		/// <summary>
		/// Gets the upper angular limit, in radians, for a Revolute joint.
		/// </summary>
		/// <returns>Upper angular limit, in radians</returns>
		float GetRevoluteUpper() const noexcept;

		/// <summary>
		/// Sets the target angular velocity of the drive for a Revolute joint. Only applies when the joint type is Revolute.
		/// </summary>
		/// <param name="velocity">Drive velocity</param>
		void SetRevoluteDriveVelocity(float velocity);
		/// <summary>
		/// Gets the target angular velocity of the drive for a Revolute joint.
		/// </summary>
		/// <returns>Drive velocity</returns>
		float GetRevoluteDriveVelocity() const noexcept;

		/// <summary>
		/// Sets the maximum force the drive can exert for a Revolute joint. Only applies when the joint type is Revolute.
		/// </summary>
		/// <param name="limit">Drive force limit</param>
		void SetRevoluteDriveForceLimit(float limit);
		/// <summary>
		/// Gets the maximum force the drive can exert for a Revolute joint.
		/// </summary>
		/// <returns>Drive force limit</returns>
		float GetRevoluteDriveForceLimit() const noexcept;

		/// <summary>
		/// Sets whether the Revolute joint's drive can spin freely without applying negative torque to slow down. Only applies when the joint type is Revolute.
		/// </summary>
		/// <param name="freespin">True to enable freespin, false otherwise</param>
		void SetRevoluteFreespin(bool freespin);
		/// <summary>
		/// Gets whether the Revolute joint's drive can spin freely.
		/// </summary>
		/// <returns>True if freespin is enabled, false otherwise</returns>
		bool GetRevoluteFreespin() const noexcept;

		/// <summary>
		/// Sets the lower linear limit for a Prismatic joint. Only applies when the joint type is Prismatic.
		/// </summary>
		/// <param name="lower">Lower linear limit</param>
		void SetPrismaticLower(float lower);
		/// <summary>
		/// Gets the lower linear limit for a Prismatic joint.
		/// </summary>
		/// <returns>Lower linear limit</returns>
		float GetPrismaticLower() const noexcept;

		/// <summary>
		/// Sets the upper linear limit for a Prismatic joint. Only applies when the joint type is Prismatic.
		/// </summary>
		/// <param name="upper">Upper linear limit</param>
		void SetPrismaticUpper(float upper);
		/// <summary>
		/// Gets the upper linear limit for a Prismatic joint.
		/// </summary>
		/// <returns>Upper linear limit</returns>
		float GetPrismaticUpper() const noexcept;

		/// <summary>
		/// Sets the motion type of the X axis for a D6 joint (0 = Locked, 1 = Limited, 2 = Free). Only applies when the joint type is D6.
		/// </summary>
		/// <param name="motion">Motion type</param>
		void SetD6MotionX(int motion);
		/// <summary>
		/// Gets the motion type of the X axis for a D6 joint.
		/// </summary>
		/// <returns>Motion type</returns>
		int GetD6MotionX() const noexcept;

		/// <summary>
		/// Sets the motion type of the Y axis for a D6 joint (0 = Locked, 1 = Limited, 2 = Free). Only applies when the joint type is D6.
		/// </summary>
		/// <param name="motion">Motion type</param>
		void SetD6MotionY(int motion);
		/// <summary>
		/// Gets the motion type of the Y axis for a D6 joint.
		/// </summary>
		/// <returns>Motion type</returns>
		int GetD6MotionY() const noexcept;

		/// <summary>
		/// Sets the motion type of the Z axis for a D6 joint (0 = Locked, 1 = Limited, 2 = Free). Only applies when the joint type is D6.
		/// </summary>
		/// <param name="motion">Motion type</param>
		void SetD6MotionZ(int motion);
		/// <summary>
		/// Gets the motion type of the Z axis for a D6 joint.
		/// </summary>
		/// <returns>Motion type</returns>
		int GetD6MotionZ() const noexcept;

		/// <summary>
		/// Sets the motion type of the twist axis for a D6 joint (0 = Locked, 1 = Limited, 2 = Free). Only applies when the joint type is D6.
		/// </summary>
		/// <param name="motion">Motion type</param>
		void SetD6MotionTwist(int motion);
		/// <summary>
		/// Gets the motion type of the twist axis for a D6 joint.
		/// </summary>
		/// <returns>Motion type</returns>
		int GetD6MotionTwist() const noexcept;

		/// <summary>
		/// Sets the motion type of the first swing axis for a D6 joint (0 = Locked, 1 = Limited, 2 = Free). Only applies when the joint type is D6.
		/// </summary>
		/// <param name="motion">Motion type</param>
		void SetD6MotionSwing1(int motion);
		/// <summary>
		/// Gets the motion type of the first swing axis for a D6 joint.
		/// </summary>
		/// <returns>Motion type</returns>
		int GetD6MotionSwing1() const noexcept;

		/// <summary>
		/// Sets the motion type of the second swing axis for a D6 joint (0 = Locked, 1 = Limited, 2 = Free). Only applies when the joint type is D6.
		/// </summary>
		/// <param name="motion">Motion type</param>
		void SetD6MotionSwing2(int motion);
		/// <summary>
		/// Gets the motion type of the second swing axis for a D6 joint.
		/// </summary>
		/// <returns>Motion type</returns>
		int GetD6MotionSwing2() const noexcept;

		/// <summary>
		/// Sets the linear limit distance for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="limit">Linear limit</param>
		void SetD6LinearLimit(float limit);
		/// <summary>
		/// Gets the linear limit distance for a D6 joint.
		/// </summary>
		/// <returns>Linear limit</returns>
		float GetD6LinearLimit() const noexcept;

		/// <summary>
		/// Sets the lower twist angular limit, in radians, for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="lower">Lower twist limit, in radians</param>
		void SetD6TwistLower(float lower);
		/// <summary>
		/// Gets the lower twist angular limit, in radians, for a D6 joint.
		/// </summary>
		/// <returns>Lower twist limit, in radians</returns>
		float GetD6TwistLower() const noexcept;

		/// <summary>
		/// Sets the upper twist angular limit, in radians, for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="upper">Upper twist limit, in radians</param>
		void SetD6TwistUpper(float upper);
		/// <summary>
		/// Gets the upper twist angular limit, in radians, for a D6 joint.
		/// </summary>
		/// <returns>Upper twist limit, in radians</returns>
		float GetD6TwistUpper() const noexcept;

		/// <summary>
		/// Sets the Y swing angle, in radians, of the limit cone for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="angle">Y swing angle, in radians</param>
		void SetD6SwingYAngle(float angle);
		/// <summary>
		/// Gets the Y swing angle, in radians, of the limit cone for a D6 joint.
		/// </summary>
		/// <returns>Y swing angle, in radians</returns>
		float GetD6SwingYAngle() const noexcept;

		/// <summary>
		/// Sets the Z swing angle, in radians, of the limit cone for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="angle">Z swing angle, in radians</param>
		void SetD6SwingZAngle(float angle);
		/// <summary>
		/// Gets the Z swing angle, in radians, of the limit cone for a D6 joint.
		/// </summary>
		/// <returns>Z swing angle, in radians</returns>
		float GetD6SwingZAngle() const noexcept;

		/// <summary>
		/// Sets the spring stiffness of the drive for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="stiffness">Drive stiffness</param>
		void SetD6DriveStiffness(float stiffness);
		/// <summary>
		/// Gets the spring stiffness of the drive for a D6 joint.
		/// </summary>
		/// <returns>Drive stiffness</returns>
		float GetD6DriveStiffness() const noexcept;

		/// <summary>
		/// Sets the damping of the drive for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="damping">Drive damping</param>
		void SetD6DriveDamping(float damping);
		/// <summary>
		/// Gets the damping of the drive for a D6 joint.
		/// </summary>
		/// <returns>Drive damping</returns>
		float GetD6DriveDamping() const noexcept;

		/// <summary>
		/// Sets the maximum force the drive can exert for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="limit">Drive force limit</param>
		void SetD6DriveForceLimit(float limit);
		/// <summary>
		/// Gets the maximum force the drive can exert for a D6 joint.
		/// </summary>
		/// <returns>Drive force limit</returns>
		float GetD6DriveForceLimit() const noexcept;

		/// <summary>
		/// Sets whether the D6 joint's drive forces account for the actor's mass and inertia (acceleration mode). Only applies when the joint type is D6.
		/// </summary>
		/// <param name="acceleration">True to use acceleration drive mode, false otherwise</param>
		void SetD6DriveAcceleration(bool acceleration);
		/// <summary>
		/// Gets whether the D6 joint's drive uses acceleration mode.
		/// </summary>
		/// <returns>True if acceleration drive mode is enabled, false otherwise</returns>
		bool GetD6DriveAcceleration() const noexcept;

		/// <summary>
		/// Sets the target position of the drive for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="position">Drive target position</param>
		void SetD6DrivePosition(const Math::Vector3& position);
		/// <summary>
		/// Gets the target position of the drive for a D6 joint.
		/// </summary>
		/// <returns>Drive target position</returns>
		Math::Vector3 GetD6DrivePosition() const noexcept;

		/// <summary>
		/// Sets the target rotation of the drive for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="rotation">Drive target rotation</param>
		void SetD6DriveRotation(const Math::Quaternion& rotation);
		/// <summary>
		/// Gets the target rotation of the drive for a D6 joint.
		/// </summary>
		/// <returns>Drive target rotation</returns>
		Math::Quaternion GetD6DriveRotation() const noexcept;

		/// <summary>
		/// Sets the target linear velocity of the drive for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="velocity">Drive target linear velocity</param>
		void SetD6DriveLinearVelocity(const Math::Vector3& velocity);
		/// <summary>
		/// Gets the target linear velocity of the drive for a D6 joint.
		/// </summary>
		/// <returns>Drive target linear velocity</returns>
		Math::Vector3 GetD6DriveLinearVelocity() const noexcept;

		/// <summary>
		/// Sets the target angular velocity of the drive for a D6 joint. Only applies when the joint type is D6.
		/// </summary>
		/// <param name="velocity">Drive target angular velocity</param>
		void SetD6DriveAngularVelocity(const Math::Vector3& velocity);
		/// <summary>
		/// Gets the target angular velocity of the drive for a D6 joint.
		/// </summary>
		/// <returns>Drive target angular velocity</returns>
		Math::Vector3 GetD6DriveAngularVelocity() const noexcept;

		/// <summary>
		/// Gets the underlying physics engine joint implementation.
		/// </summary>
		/// <returns>Pointer to the underlying joint</returns>
		IJoint* GetJoint() const noexcept;

	private:
		void _updateJointParameters();
		void _resolveActors();
	};
}

REFL_FWD(Joint)
