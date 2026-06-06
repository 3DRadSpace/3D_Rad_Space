#pragma once
#include "../../Objects/IObject3D.hpp"
#include "../IPhysicsEngine.hpp"
#include "../ICollider.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// Base class for all objects that interact with the physics engine.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT IPhysicsObject : public Engine3DRadSpace::Objects::IObject3D
	{
	protected:
		IPhysicsEngine* _physics;
		IPhysicsObject() = default;
		IPhysicsObject(
			const std::string& name,
			bool enabled,
			bool visible,
			const Math::Vector3& position,
			const Math::Quaternion& rotation,
			const Math::Vector3& scale
		);

		IPhysicsObject(const IPhysicsObject&) = delete;
		IPhysicsObject& operator=(const IPhysicsObject&) = delete;

		IPhysicsObject(IPhysicsObject&&) noexcept = default;
		IPhysicsObject& operator=(IPhysicsObject&&) noexcept = default;
	public:
		void Initialize() override;

		virtual ~IPhysicsObject() = default;
	};
}