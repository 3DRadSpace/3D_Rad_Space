#pragma once
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Ray.hpp"
#include "../Core/IUpdateable.hpp"

namespace Engine3DRadSpace::Physics
{
	class IPhysicsEngine;
	/// <summary>
	/// Base polymorphic type for physics objects that interact with the scene.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT ICollider
	{
	protected:
		IPhysicsEngine* _physics;

		float _mass = 1.0f;
		Math::Vector3 _position;
		Math::Quaternion _rotation;

		ICollider(IPhysicsEngine* physics);

		ICollider(const ICollider&) = delete;
		ICollider& operator=(const ICollider&) = delete;

		ICollider(ICollider&&) noexcept = default;
		ICollider& operator=(ICollider&&) noexcept = default;
	public:
		/// <summary>
		/// Gets the mass of this collider.
		/// </summary>
		/// <returns>Mass in kilograms</returns>
		virtual float GetMass() const = 0;
		/// <summary>
		/// Sets the mass of this collider.
		/// </summary>
		/// <param name="mass">Mass in kilograms</param>
		virtual void SetMass(float mass) = 0;

		/// <summary>
		/// Gets the position of this collider.
		/// </summary>
		/// <returns>The position vector.</returns>
		virtual Math::Vector3 GetPosition() const = 0;
		/// <summary>
		/// Sets the position of this collider.
		/// </summary>
		/// <param name="position">The position vector.</param>
		virtual void SetPosition(const Math::Vector3& position) = 0;
		/// <summary>
		/// Gets the rotation of this collider.
		/// </summary>
		/// <returns>The rotation quaternion.</returns>
		virtual Math::Quaternion GetRotation() const = 0;
		/// <summary>
		/// Sets the rotation of this collider.
		/// </summary>
		/// <param name="rotation">The rotation quaternion.</param>
		virtual void SetRotation(const Math::Quaternion& rotation) = 0;
		/// <summary>
		/// Gets the physics engine that this collider is associated with.
		/// </summary>
		/// <returns></returns>
		IPhysicsEngine* GetPhysics() const noexcept;
		/// <summary>
		/// Returns the distance from the ray origin to the intersection point if the ray intersects with this collider, or std::nullopt if there is no intersection.
		/// </summary>
		/// <param name="r">The ray to test for intersection.</param>
		/// <returns>The distance from the ray origin to the intersection point, or std::nullopt if there is no intersection.</returns>
		virtual std::optional<float> Intersects(const Math::Ray& r) = 0;
		/// <summary>
		/// Update the transform of this collider in the physics engine. This method should be called after changing the position or rotation of the collider to ensure that the physics engine is aware of the changes.
		/// </summary>
		virtual void UpdateTransform() = 0;
		/// <summary>
		/// Update the transform of this collider in the physics engine with the specified position and rotation. This method should be called after changing the position or rotation of the collider to ensure that the physics engine is aware of the changes.
		/// </summary>
		/// <param name="position">The position vector.</param>
		/// <param name="rotation">The rotation quaternion.</param>
		virtual void UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation) = 0;

		virtual ~ICollider() = default;
	};
}