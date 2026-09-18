#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Physics
{
	class IPhysicsEngine;

	/// <summary>
	/// Polymorphic base type for all physics actors. Examples include colliders, joints, etc.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT IPhysicsActor
	{
	protected:
		IPhysicsEngine* _physics;

		IPhysicsActor(IPhysicsEngine* physics);
	public:
		/// <summary>
		/// Gets the physics engine that this collider is associated with.
		/// </summary>
		/// <returns></returns>
		IPhysicsEngine* GetPhysics() const noexcept;

		virtual ~IPhysicsActor() = default;
	};
}