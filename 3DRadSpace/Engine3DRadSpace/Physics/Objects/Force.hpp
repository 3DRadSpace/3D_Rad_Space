#pragma once
#include "IPhysicsObject.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// Represents a force that can affect a dynamic physics object. The affected object is the parent of this object.
	/// </summary>
	class Force : public IPhysicsObject
	{
		Math::Vector3 _direction = Math::Vector3::Forward();
		float _time = 0;
	public:
		/// <summary>
		/// Complete force constructor.
		/// </summary>
		/// <param name="name">Name of this object</param>
		/// <param name="position">Initial position of the force</param>
		/// <param name="rotation">Initial rotation of the force</param>
		/// <param name="magnitude">Magnitude of the force</param>
		/// <param name="timer">Duration for which the force is applied</param>
		/// <param name="torque">Indicates whether the force is a torque</param>
		Force(
			const std::string& name = "Force",
			const Math::Vector3& position = Math::Vector3(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			float magnitude = 1,
			float timer = 1.0f,
			bool torque = false
		);

		Force(Force&&) noexcept = default;
		Force& operator=(Force&&) noexcept = default;
		/// <summary>
		/// Magnitude of this force.
		/// </summary>
		float Magnitude;
		/// <summary>
		///	How long is this force applied in seconds.
		/// </summary>
		float Timer;
		/// <summary>
		/// Indicates whether the force is a torque.
		/// </summary>
		bool Torque;
		/// <summary>
		/// Normalized direction of the force.
		/// </summary>
		/// <returns>The normalized direction vector of the force.</returns>
		Math::Vector3 Direction() const noexcept;
		/// <summary>
		/// Calculates the force vector based on magnitude and direction.
		/// </summary>
		/// <returns>The force vector.</returns>
		Math::Vector3 ForceVector() const noexcept;
		/// <summary>
		///	Enables the force, allowing it to affect physics objects. This method is called when the force is activated in the simulation.
		/// </summary>
		void Enable() override;
		/// <summary>
		/// Stops the force from affecting physics objects.
		/// </summary>
		void Disable() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		///	Does nothing.
		/// </summary>
		/// <param name="path"></param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Updates the internal timer and applies the force.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Returns NaN
		/// </summary>
		/// <param name="r">unused</param>
		/// <returns>NaN</returns>
		float Intersects(const Math::Ray& r) const override;
		/// <summary>
		/// Returns the UUID of the Force class.
		/// </summary>
		/// <returns>{D8826FCB-E3A3-4887-94B2-ADF0C094F2ED}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Returns the gizmo associated with this object.
		/// </summary>
		/// <returns>The gizmo associated with this object.</returns>
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}

REFL_FWD(Force)