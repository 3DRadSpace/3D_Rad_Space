#pragma once
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Ray.hpp"
#include "../Core/IUpdateable.hpp"

namespace Engine3DRadSpace::Physics
{
	class IPhysicsEngine;

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
		virtual float GetMass() const = 0;
		virtual void SetMass(float mass) = 0;

		virtual Math::Vector3 GetPosition() const = 0;
		virtual void SetPosition(const Math::Vector3& position) = 0;

		virtual Math::Quaternion GetRotation() const = 0;
		virtual void SetRotation(const Math::Quaternion& rotation) = 0;

		IPhysicsEngine* GetPhysics() const noexcept;

		virtual std::optional<float> Intersects(const Math::Ray& r) = 0;
		virtual void UpdateTransform() = 0;
		virtual void UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation) = 0;

		virtual ~ICollider() = default;
	};
}