#pragma once
#include "../IJoint.hpp"
#include "PxUptr.hpp"
#include <extensions/PxFixedJoint.h>
#include <extensions/PxDistanceJoint.h>
#include <extensions/PxSphericalJoint.h>
#include <extensions/PxRevoluteJoint.h>
#include <extensions/PxPrismaticJoint.h>
#include <extensions/PxD6Joint.h>

namespace Engine3DRadSpace::Physics::NVPhysX
{
	class DynamicCollider;
	class E3DRSP_PHYSICS_OBJ_EXPORT Joint : public IJoint
	{
	protected:
		PxUPtr<physx::PxJoint> _joint;

		void _createJoint();
		void _destroyJoint();

	public:
		Joint(IPhysicsEngine* physics, JointType type);

		Joint(Joint&&) noexcept = default;
		Joint& operator=(Joint&&) noexcept = default;

		void SetActors(IDynamicCollider* actor0, IDynamicCollider* actor1) override;

		void SetLocalFrame0(const Math::Vector3& position, const Math::Quaternion& rotation) override;
		void SetLocalFrame1(const Math::Vector3& position, const Math::Quaternion& rotation) override;

		void SetBreakForce(float force, float torque) override;

		void GetForce(Math::Vector3& linear, Math::Vector3& angular) override;

		void SetDistanceLimit(float minDistance, float maxDistance) override;

		void SetSphericalLimit(float yAngle, float zAngle) override;

		void SetRevoluteLimit(float lower, float upper) override;
		void SetRevoluteDrive(float velocity, float forceLimit, bool freespin) override;

		void SetPrismaticLimit(float lower, float upper) override;

		void SetD6Motion(int axis, int motionType) override;
		void SetD6LinearLimit(float limit) override;
		void SetD6TwistLimit(float lower, float upper) override;
		void SetD6SwingLimit(float yAngle, float zAngle) override;
		void SetD6Drive(int driveType, float stiffness, float damping, float forceLimit, bool acceleration) override;
		void SetD6DrivePosition(const Math::Vector3& position, const Math::Quaternion& rotation) override;
		void SetD6DriveVelocity(const Math::Vector3& linear, const Math::Vector3& angular) override;

		~Joint() override;

		friend class PhysicsEngine;
		friend class DynamicCollider;
	};
}
