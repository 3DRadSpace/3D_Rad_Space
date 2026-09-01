#pragma once
#include "../../Objects/IObject3D.hpp"
#include "../IPhysicsEngine.hpp"
#include "../ICollider.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// Base class for all objects that interact with the physics engine.
	/// </summary>
	class E3DRSP_PHYSICS_OBJ_EXPORT IPhysicsObject : public Engine3DRadSpace::Objects::IObject3D
	{
	protected:
		IPhysicsEngine* _physics = nullptr;
		IPhysicsObject() = default;
		/// <summary>
		/// Complete IPhysicsObject interface constructor.
		/// </summary>
		/// <param name="name">Name of this object</param>
		/// <param name="enabled">Indicates whether this object is enabled</param>
		/// <param name="visible">Indicates whether this object is visible</param>
		/// <param name="position">Initial position of this object</param>
		/// <param name="rotation">Initial rotation of this object</param>
		/// <param name="scale">Initial scale of this object</param>
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
		/// <summary>
		/// Loads the relevant services.
		/// </summary>
		void Initialize() override;

		virtual ~IPhysicsObject() = default;
	};
}