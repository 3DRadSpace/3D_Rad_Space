#pragma once
#include "JointType.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"

namespace Engine3DRadSpace::Physics
{
	class IPhysicsEngine;
	class IDynamicCollider;

	/// <summary>
	/// Base interface for all physics joints.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT IJoint
	{
	protected:
		IPhysicsEngine* _physics;
		JointType _type;

		IDynamicCollider* _actor0;
		IDynamicCollider* _actor1;

		Math::Vector3 _localFrame0Position;
		Math::Quaternion _localFrame0Rotation;
		Math::Vector3 _localFrame1Position;
		Math::Quaternion _localFrame1Rotation;

		float _breakForce;
		float _breakTorque;
		bool _isBroken;

		IJoint(IPhysicsEngine* physics, JointType type);

		IJoint(const IJoint&) = delete;
		IJoint& operator=(const IJoint&) = delete;

		IJoint(IJoint&&) noexcept = default;
		IJoint& operator=(IJoint&&) noexcept = default;

	public:
		virtual ~IJoint() = default;

		/// <summary>
		/// Gets the joint type.
		/// </summary>
		JointType GetType() const noexcept;

		/// <summary>
		/// Sets the actors connected by this joint.
		/// </summary>
		virtual void SetActors(IDynamicCollider* actor0, IDynamicCollider* actor1) = 0;

		/// <summary>
		/// Gets the first actor in the joint.
		/// </summary>
		IDynamicCollider* GetActor0() const noexcept;

		/// <summary>
		/// Gets the second actor in the joint.
		/// </summary>
		IDynamicCollider* GetActor1() const noexcept;

		/// <summary>
		/// Sets the local frame for actor 0.
		/// </summary>
		virtual void SetLocalFrame0(const Math::Vector3& position, const Math::Quaternion& rotation) = 0;

		/// <summary>
		/// Sets the local frame for actor 1.
		/// </summary>
		virtual void SetLocalFrame1(const Math::Vector3& position, const Math::Quaternion& rotation) = 0;

		/// <summary>
		/// Gets the local frame position for actor 0.
		/// </summary>
		Math::Vector3 GetLocalFrame0Position() const noexcept;

		/// <summary>
		/// Gets the local frame rotation for actor 0.
		/// </summary>
		Math::Quaternion GetLocalFrame0Rotation() const noexcept;

		/// <summary>
		/// Gets the local frame position for actor 1.
		/// </summary>
		Math::Vector3 GetLocalFrame1Position() const noexcept;

		/// <summary>
		/// Gets the local frame rotation for actor 1.
		/// </summary>
		Math::Quaternion GetLocalFrame1Rotation() const noexcept;

		/// <summary>
		/// Sets the break force and torque thresholds.
		/// </summary>
		virtual void SetBreakForce(float force, float torque) = 0;

		/// <summary>
		/// Gets the break force threshold.
		/// </summary>
		float GetBreakForce() const noexcept;

		/// <summary>
		/// Gets the break torque threshold.
		/// </summary>
		float GetBreakTorque() const noexcept;

		/// <summary>
		/// Returns true if the joint has broken.
		/// </summary>
		bool IsBroken() const noexcept;

		/// <summary>
		/// Gets the constraint force applied by the joint.
		/// </summary>
		virtual void GetForce(Math::Vector3& linear, Math::Vector3& angular) = 0;

		// Joint type-specific parameters (using floats as requested, no unions/variants)

		/// <summary>
		/// Sets distance joint parameters (min/max distance).
		/// </summary>
		virtual void SetDistanceLimit(float minDistance, float maxDistance) = 0;

		/// <summary>
		/// Sets spherical joint cone limit (yAngle, zAngle in radians).
		/// </summary>
		virtual void SetSphericalLimit(float yAngle, float zAngle) = 0;

		/// <summary>
		/// Sets revolute joint angular limits (lower, upper in radians).
		/// </summary>
		virtual void SetRevoluteLimit(float lower, float upper) = 0;

		/// <summary>
		/// Sets revolute joint drive parameters.
		/// </summary>
		virtual void SetRevoluteDrive(float velocity, float forceLimit, bool freespin) = 0;

		/// <summary>
		/// Sets prismatic joint linear limits.
		/// </summary>
		virtual void SetPrismaticLimit(float lower, float upper) = 0;

		/// <summary>
		/// Sets D6 joint motion for a specific axis (0=locked, 1=limited, 2=free).
		/// axis: 0-2=translation X/Y/Z, 3=twist, 4-5=swing1/swing2
		/// </summary>
		virtual void SetD6Motion(int axis, int motionType) = 0;

		/// <summary>
		/// Sets D6 joint linear limit.
		/// </summary>
		virtual void SetD6LinearLimit(float limit) = 0;

		/// <summary>
		/// Sets D6 joint twist limit (lower, upper in radians).
		/// </summary>
		virtual void SetD6TwistLimit(float lower, float upper) = 0;

		/// <summary>
		/// Sets D6 joint swing limit (yAngle, zAngle in radians).
		/// </summary>
		virtual void SetD6SwingLimit(float yAngle, float zAngle) = 0;

		/// <summary>
		/// Sets D6 joint drive parameters.
		/// driveType: 0=X, 1=Y, 2=Z, 3=Swing, 4=Twist, 5=SLERP
		/// </summary>
		virtual void SetD6Drive(int driveType, float stiffness, float damping, float forceLimit, bool acceleration) = 0;

		/// <summary>
		/// Sets D6 joint drive position target.
		/// </summary>
		virtual void SetD6DrivePosition(const Math::Vector3& position, const Math::Quaternion& rotation) = 0;

		/// <summary>
		/// Sets D6 joint drive velocity target.
		/// </summary>
		virtual void SetD6DriveVelocity(const Math::Vector3& linear, const Math::Vector3& angular) = 0;
	};
}
