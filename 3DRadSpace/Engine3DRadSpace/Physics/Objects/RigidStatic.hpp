#pragma once
#include "IPhysicsObject.hpp"
#include "../IStaticCollider.hpp"
#include "../../Objects/Impl/Skinmesh.hpp"
#include "../../Graphics/Rendering/RenderingManager.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// Represents an static rigidboby made from an mesh collider.
	/// </summary>
	class E3DRSP_PHYSICS_OBJ_EXPORT RigidStatic : public IPhysicsObject
	{
		std::unique_ptr<IStaticCollider> _collider = nullptr;
		std::unique_ptr<std::string> _path;

		Graphics::Model3D* _model = nullptr;
		bool _reqTransformUpdate = false;

		struct physicsProperties
		{
			float linearDamping = 0.0f;
			float staticFriction = 0.0f;
			float dynamicFriction = 0.0f;
			float restitution = 0.0f;
		};

		std::unique_ptr<physicsProperties> _properties = std::make_unique<physicsProperties>();
		Graphics::Rendering::RenderingManager* _renderingManager = nullptr;
	public:
		/// <summary>
		/// Default constructor for RigidStatic. Initializes the object with default values.
		/// </summary>
		RigidStatic();
		/// <summary>
		/// RigidStatic constructor using an path to a model file.
		/// </summary>
		/// <param name="name">Name of this object</param>
		/// <param name="enabled">Indicates whether this object is enabled</param>
		/// <param name="visible">Indicates whether this object is visible</param>
		/// <param name="path">Path to the model file</param>
		/// <param name="position">Initial position of this object</param>
		/// <param name="rotation">Initial rotation of this object</param>
		/// <param name="scale">Initial scale of this object</param>
		RigidStatic(
			const std::string& name,
			bool enabled,
			bool visible,
			const std::filesystem::path& path,
			const Math::Vector3 position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3::One()
		);

		RigidStatic(RigidStatic&&) noexcept = default;
		RigidStatic& operator=(RigidStatic&&) noexcept = default;
		/// <summary>
		///	Numerical asset identifier for the model used as a static collider for this RigidStatic instance.
		/// </summary>
		Engine3DRadSpace::Objects::RefModel3D Model;
		/// <summary>
		/// Gets the linear damping.
		/// </summary>
		/// <returns>The linear damping value.</returns>
		float GetLinearDamping() const noexcept;
		void SetLinearDamping(float linearDamping);

		/// <summary>
		/// Gets the static friction.
		/// </summary>
		/// <returns>The static friction value.</returns>
		float GetStaticFriction() const noexcept;
		void SetStaticFriction(float friction);

		/// <summary>
		/// Gets the dynamic friction.
		/// </summary>
		/// <returns>The dynamic friction value.</returns>
		float GetDynamicFriction() const noexcept;
		void SetDynamicFriction(float friction);

		/// <summary>
		/// Gets the restitution.
		/// </summary>
		/// <returns>The restitution value.</returns>
		float GetRestitution() const noexcept;
		void SetRestitution(float restitution);
		/// <summary>
		/// Retrieves relevant services.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Loads the model and creates the static collider for this RigidStatic instance.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Loads an alternate model and recreates the underlying static collider.
		/// </summary>
		/// <param name="path">The path to the alternate model file.</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Updates the physics state for this instance.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Draws thiis instance.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Determines if the given ray intersects with this instance.
		/// </summary>
		/// <param name="r">The ray to test for intersection.</param>
		/// <returns>The distance to the intersection point, or a negative value if there is no intersection.</returns>
		float Intersects(const Math::Ray& r) const override;
		/// <summary>
		/// Gets the gizmo associated with this instance.
		/// </summary>
		/// <returns>The gizmo associated with this instance.</returns>
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
		/// <summary>
		///	Gets the UUID associated with teh RigidStatic type.
		/// </summary>
		/// <returns>{11E67CA3-19A3-4558-8528-72A03F0901F9}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Gets the underlying static collider.
		/// </summary>
		/// <returns></returns>
		IStaticCollider* GetCollider() const noexcept;
		/// <summary>
		/// Gets the model used to generate the static collider.
		/// </summary>
		/// <returns>The model used to generate the static collider.</returns>
		Graphics::Model3D* GetModel() const noexcept;
		/// <summary>
		/// Requests an update to the transform of this instance.
		/// </summary>
		void RequestTransformUpdate();
		/// <summary>
		/// Gets the bounding box of this instance.
		/// </summary>
		/// <returns>The bounding box of this instance.</returns>
		Math::BoundingBox GetBoundingBox() const noexcept override;
		
		~RigidStatic() override = default;
	};
}

REFL_FWD(RigidStatic)