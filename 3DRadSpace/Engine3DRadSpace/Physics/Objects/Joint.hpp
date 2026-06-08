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
		Joint(
			const std::string& name = "Joint",
			bool enabled = true,
			bool visible = false,
			const Math::Vector3& position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3::One()
		);

		Joint(Joint&&) noexcept = default;
		Joint& operator=(Joint&&) noexcept = default;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;
		void Draw3D() override;

		float Intersects(const Math::Ray& r) override;
		Reflection::UUID GetUUID() const noexcept override;
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		JointType GetJointType() const noexcept;
		void SetJointType(JointType type);

		void SetActor0(Engine3DRadSpace::Objects::ObjectID actorID);
		void SetActor1(Engine3DRadSpace::Objects::ObjectID actorID);

		Engine3DRadSpace::Objects::ObjectID GetActor0() const noexcept;
		Engine3DRadSpace::Objects::ObjectID GetActor1() const noexcept;

		void SetLocalFrame0Position(const Math::Vector3& position);
		Math::Vector3 GetLocalFrame0Position() const noexcept;

		void SetLocalFrame0Rotation(const Math::Quaternion& rotation);
		Math::Quaternion GetLocalFrame0Rotation() const noexcept;

		void SetLocalFrame1Position(const Math::Vector3& position);
		Math::Vector3 GetLocalFrame1Position() const noexcept;

		void SetLocalFrame1Rotation(const Math::Quaternion& rotation);
		Math::Quaternion GetLocalFrame1Rotation() const noexcept;

		void SetBreakForce(float force);
		float GetBreakForce() const noexcept;

		void SetBreakTorque(float torque);
		float GetBreakTorque() const noexcept;

		bool IsBroken() const noexcept;

		void SetDistanceMin(float min);
		float GetDistanceMin() const noexcept;

		void SetDistanceMax(float max);
		float GetDistanceMax() const noexcept;

		void SetSphericalYAngle(float angle);
		float GetSphericalYAngle() const noexcept;

		void SetSphericalZAngle(float angle);
		float GetSphericalZAngle() const noexcept;

		void SetRevoluteLower(float lower);
		float GetRevoluteLower() const noexcept;

		void SetRevoluteUpper(float upper);
		float GetRevoluteUpper() const noexcept;

		void SetRevoluteDriveVelocity(float velocity);
		float GetRevoluteDriveVelocity() const noexcept;

		void SetRevoluteDriveForceLimit(float limit);
		float GetRevoluteDriveForceLimit() const noexcept;

		void SetRevoluteFreespin(bool freespin);
		bool GetRevoluteFreespin() const noexcept;

		void SetPrismaticLower(float lower);
		float GetPrismaticLower() const noexcept;

		void SetPrismaticUpper(float upper);
		float GetPrismaticUpper() const noexcept;

		void SetD6MotionX(int motion);
		int GetD6MotionX() const noexcept;

		void SetD6MotionY(int motion);
		int GetD6MotionY() const noexcept;

		void SetD6MotionZ(int motion);
		int GetD6MotionZ() const noexcept;

		void SetD6MotionTwist(int motion);
		int GetD6MotionTwist() const noexcept;

		void SetD6MotionSwing1(int motion);
		int GetD6MotionSwing1() const noexcept;

		void SetD6MotionSwing2(int motion);
		int GetD6MotionSwing2() const noexcept;

		void SetD6LinearLimit(float limit);
		float GetD6LinearLimit() const noexcept;

		void SetD6TwistLower(float lower);
		float GetD6TwistLower() const noexcept;

		void SetD6TwistUpper(float upper);
		float GetD6TwistUpper() const noexcept;

		void SetD6SwingYAngle(float angle);
		float GetD6SwingYAngle() const noexcept;

		void SetD6SwingZAngle(float angle);
		float GetD6SwingZAngle() const noexcept;

		void SetD6DriveStiffness(float stiffness);
		float GetD6DriveStiffness() const noexcept;

		void SetD6DriveDamping(float damping);
		float GetD6DriveDamping() const noexcept;

		void SetD6DriveForceLimit(float limit);
		float GetD6DriveForceLimit() const noexcept;

		void SetD6DriveAcceleration(bool acceleration);
		bool GetD6DriveAcceleration() const noexcept;

		void SetD6DrivePosition(const Math::Vector3& position);
		Math::Vector3 GetD6DrivePosition() const noexcept;

		void SetD6DriveRotation(const Math::Quaternion& rotation);
		Math::Quaternion GetD6DriveRotation() const noexcept;

		void SetD6DriveLinearVelocity(const Math::Vector3& velocity);
		Math::Vector3 GetD6DriveLinearVelocity() const noexcept;

		void SetD6DriveAngularVelocity(const Math::Vector3& velocity);
		Math::Vector3 GetD6DriveAngularVelocity() const noexcept;

		IJoint* GetJoint() const noexcept;

	private:
		void _updateJointParameters();
		void _resolveActors();
	};
}

REFL_FWD(Joint)
