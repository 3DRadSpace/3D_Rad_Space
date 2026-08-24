#pragma once
#include "IPhysicsObject.hpp"
#include "../IDynamicCollider.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// A physics object with a dynamic rigidbody collider.
	/// </summary>
	/// <remarks>
	/// The children of this object are used to determine the collider shape.
	/// The supported collider shapes are:
	/// - Box 
	/// - Sphere
	/// </remarks>
	class E3DRSP_PHYSICS_EXPORT RigidDynamic : public IPhysicsObject
	{
	protected:
		std::unique_ptr<IDynamicCollider> _collider;

		struct physicsProperties
		{
			float mass = 1.0f;
			float linearDamping = 0.0f;
			float angularDamping = 0.05f;
			float staticFriction = 0.5f;
			float dynamicFriction = 0.5f;
			float restitution = 0.5f;
			Math::Vector3 linearVelocity = Math::Vector3::Zero();
			Math::Vector3 angularVelocity = Math::Vector3::Zero();
			Math::Vector3 maxAngularVelocity = Math::Vector3(100.0f, 100.0f, 100.0f);
		};

		std::unique_ptr<physicsProperties> _properties = std::make_unique<physicsProperties>();

		bool _kinematic = false;
		
		Math::BoundingBox _bbox;
	public:
		/// <summary>
		/// RigidDynamic constructor.
		/// </summary>
		/// <param name="name">Name of this object</param>
		/// <param name="enabled">Indicates whether this object is enabled</param>
		/// <param name="visible">Indicates whether this object is visible</param>
		/// <param name="position">Initial position of this object</param>
		/// <param name="rotation">Initial rotation of this object</param>
		/// <param name="scale">Initial scale of this object</param>
		RigidDynamic(
			const std::string& name = "RigidDynamic",
			bool enabled = true,
			bool visible = true,
			const Math::Vector3& position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3::One()
		);

		RigidDynamic(RigidDynamic&&) noexcept = default;
		RigidDynamic& operator=(RigidDynamic&&) noexcept = default;
		/// <summary>
		/// Retrieves relevant services and updates the collider properties.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="path">Unused.</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Updates the position and rotation of this object based on the collider's state.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Returns NaN.
		/// </summary>
		/// <param name="r">The ray to test for intersection.</param>
		/// <returns>NaN if there is no intersection, otherwise the distance to the intersection point.</returns>
		float Intersects(const Math::Ray& r) const override;
		/// <summary>
		/// Gets the bounding box of this object.
		/// </summary>
		/// <returns>The bounding box of this object.</returns>
		Math::BoundingBox GetBoundingBox() const noexcept override;
		/// <summary>
		/// Returns the UUID associated with the type RigidDynamic.
		/// </summary>
		/// <returns>{E360B70E-266C-4B9B-A14C-62979B930D3C}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Returns the gizmo associated with this object.
		/// </summary>
		/// <returns>The gizmo associated with this object.</returns>
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
		/// <summary>
		/// Teleports this object at the specified position and rotation. If rotation is not provided, the current rotation is maintained.
		/// </summary>
		/// <param name="position">The position to teleport to.</param>
		/// <param name="rotation">The rotation to teleport to. If not provided, the current rotation is maintained.</param>
		void Teleport(const Math::Vector3& position, const std::optional<Math::Quaternion>& rotation = std::nullopt);
		/// <summary>
		/// Gets the mass of this object in kg. The default mass is 1.0 kg.
		/// </summary>
		/// <returns>The mass of this object in kg.</returns>
		float GetMass() const noexcept;
		/// <summary>
		/// Sets the mass of this object. The mass must be greater than 0.0 kg.
		/// </summary>
		/// <param name="mass">Mass in kilograms</param>
		void SetMass(float mass);
		/// <summary>
		/// Gets the linear damping coefficent.
		/// </summary>
		/// <returns>Linear damping.</returns>
		float GetLinearDamping() const noexcept;
		/// <summary>
		/// Sets the linear damping coefficient. The linear damping must be greater than or equal to 0.0.
		/// </summary>
		/// <param name="linearDamping">Linear damping coefficient</param>
		void SetLinearDamping(float linearDamping);

		/// <summary>
		/// Gets the angular damping coefficient.
		/// </summary>
		/// <returns>Angular damping.</returns>
		float GetAngularDamping() const noexcept;
		/// <summary>
		/// Sets the angular damping coefficient. The angular damping must be greater than or equal to 0.0.
		/// </summary>
		/// <param name="angularDamping">Angular damping coefficient</param>
		void SetAngularDamping(float angularDamping);
		/// <summary>
		/// Gets the static friction coefficient. The default static friction is 0.5.
		/// </summary>
		/// <returns>Static friction coefficient</returns>
		float GetStaticFriction() const noexcept;
		/// <summary>
		/// Sets the static friction coefficient. The static friction must be greater than or equal to 0.0.
		/// </summary>
		/// <param name="friction">Static friction coefficient</param>
		void SetStaticFriction(float friction);

		/// <summary>
		/// Gets the dynamic friction coefficient. The default dynamic friction is 0.5.
		/// </summary>
		/// <returns>Dynamic friction coefficient</returns>
		float GetDynamicFriction() const noexcept;
		/// <summary>
		/// Sets the dynamic friction coefficient. The dynamic friction must be greater than or equal to 0.0.
		/// </summary>
		/// <param name="friction">Dynamic friction coefficient</param>
		void SetDynamicFriction(float friction);

		/// <summary>
		/// Gets the restitution coefficient. The default restitution is 0.5.
		/// </summary>
		/// <returns>Restitution coefficient</returns>
		float GetRestitution() const noexcept;
		/// <summary>
		/// Sets the restitution coefficient. The restitution must be greater than or equal to 0.0.
		/// </summary>
		/// <param name="restitution">Restitution coefficient</param>
		void SetRestitution(float restitution);

		/// <summary>
		/// Gets the linear velocity of this object.
		/// </summary>
		/// <returns>Linear velocity</returns>
		Math::Vector3 GetLinearVelocity() const noexcept;
		/// <summary>
		/// Sets the linear velocity of this object. The linear velocity is in world space.
		/// </summary>
		/// <param name="linearVelocity"></param>
		void SetLinearVelocity(const Math::Vector3& linearVelocity);
		/// <summary>
		/// Gets the angular velocity(spin) of this object in world space.
		/// </summary>
		/// <returns>Angular velocity</returns>
		Math::Vector3 GetAngularVelocity() const noexcept;
		/// <summary>
		/// Sets the spin of this object in world space. The angular velocity is in radians per second.
		/// </summary>
		/// <param name="angularVelocity">Angular velocity in radians per second</param>
		void SetAngularVelocity(const Math::Vector3& angularVelocity);
		/// <summary>
		/// Gets the maximum angular velocity this object can have.
		/// </summary>
		/// <returns>Maximum angular velocity</returns>
		Math::Vector3 GetMaxAngularVelocity() const noexcept;
		/// <summary>
		/// Sets the maximum angular velocity this object can have. The maximum angular velocity is in radians per second.
		/// </summary>
		/// <param name="maxAngularVelocity">Maximum angular velocity in radians per second</param>
		void SetMaxAngularVelocity(const Math::Vector3& maxAngularVelocity);
		/// <summary>
		/// Is this object kinematic?
		/// </summary>
		/// <returns></returns>
		bool IsKinematic() const noexcept;
		/// <summary>
		/// Set the kinematic state of this object. Kinematic objects are not affected by forces or collisions, but can be moved manually.
		/// </summary>
		/// <param name="isKinematic"></param>
		void SetKinematic(bool isKinematic);
		/// <summary>
		/// Determined the colliders of this object based on it's children.
		/// </summary>
		void ValidateChildren();

		IDynamicCollider* GetCollider() const noexcept;
	};
}

REFL_FWD(RigidDynamic)