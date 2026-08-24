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

	/// <summary>
	/// Physics engine interface.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT IPhysicsEngine : public IService
	{
	public:
		/// <summary>
		/// Simulates the world with a step in dt seconds.
		/// </summary>
		/// <param name="dt">step duration in seconds</param>
		virtual void Simulate(float dt) = 0;
		/// <summary>
		/// Gets an handle to the scene.
		/// </summary>
		/// <returns>scene handle</returns>
		virtual void* GetScene() const noexcept = 0;
		/// <summary>
		/// Creates an static collider for the given model with the specified position, rotation, and scale.
		/// </summary>
		/// <param name="model">The 3D model to create the static collider for.</param>
		/// <param name="position">The position of the static collider.</param>
		/// <param name="rotation">The rotation of the static collider.</param>
		/// <param name="scale">The scale of the static collider.</param>
		/// <returns>A unique pointer to the created static collider.</returns>
		virtual std::unique_ptr<IStaticCollider> CreateStaticCollider(
			Graphics::Model3D* model,
			const Math::Vector3 &position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3 &scale = Math::Vector3::One()
		) = 0;
		/// <summary>
		/// Creates a dynamic collider.
		/// </summary>
		/// <returns>A unique pointer to the created dynamic collider.</returns>
		virtual std::unique_ptr<IDynamicCollider> CreateDynamicCollider() = 0;
		/// <summary>
		/// Creates a character controller.
		/// </summary>
		/// <param name="radius">The radius of the character controller.</param>
		/// <param name="height">The height of the character controller.</param>
		/// <param name="position">The position of the character controller.</param>
		/// <returns>A unique pointer to the created character controller.</returns>
		virtual std::unique_ptr<ICharacterController> CreateCharacterController(float radius, float height, const Math::Vector3& position = Math::Vector3::Zero()) = 0;
		/// <summary>
		/// Creates a joint of the specified type.
		/// </summary>
		/// <param name="type">The type of joint to create.</param>
		/// <returns>A unique pointer to the created joint.</returns>
		virtual std::unique_ptr<IJoint> CreateJoint(JointType type) = 0;
		/// <summary>
		///	Returns the time step.
		/// </summary>
		/// <returns>The time step in seconds.</returns>
		virtual double dt() const noexcept = 0;
		/// <summary>
		/// Sets the simulation gravity.
		/// </summary>
		/// <param name="gravity">gravity in m/s^2</param>
		virtual void SetGravity(const Math::Vector3& gravity) = 0;
		/// <summary>
		/// Gets the simulation gravity.
		/// </summary>
		/// <returns>gravity in m/s^2</returns>
		virtual Math::Vector3 GetGravity() const = 0;

		~IPhysicsEngine() override = default;
	};
}