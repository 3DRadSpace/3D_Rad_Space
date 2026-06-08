#pragma once
#include "../Core/IService.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Model3D;
}

namespace Engine3DRadSpace::Physics
{
	class IStaticCollider;
	class IDynamicCollider;
	class ICharacterController;
	class IJoint;
	enum class JointType;

	class E3DRSP_PHYSICS_EXPORT IPhysicsEngine : public IService
	{
	public:
		virtual void Simulate(float dt) = 0;
		virtual void* GetScene() const noexcept = 0;

		virtual std::unique_ptr<IStaticCollider> CreateStaticCollider(
			Graphics::Model3D* model,
			const Math::Vector3 &position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3 &scale = Math::Vector3::One()
		) = 0;
		virtual std::unique_ptr<IDynamicCollider> CreateDynamicCollider() = 0;
		virtual std::unique_ptr<ICharacterController> CreateCharacterController(float radius, float height, const Math::Vector3& position = Math::Vector3::Zero()) = 0;
		virtual std::unique_ptr<IJoint> CreateJoint(JointType type) = 0;
		virtual double dt() const noexcept = 0;

		virtual void SetGravity(const Math::Vector3& gravity) = 0;
		virtual Math::Vector3 GetGravity() const = 0;

		~IPhysicsEngine() override = default;
	};
}