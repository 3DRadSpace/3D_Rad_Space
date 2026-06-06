#pragma once
#include "../../Objects/IObject.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// A GForce object is a object that enables physics simulation and specifies the gravity.
	/// </summary>
	/// <remarks>
	/// You can avoid using this object, by manually initializing the physics. See the Game class.
	/// </remarks>
	class E3DRSP_PHYSICS_OBJ_EXPORT GForce : public Engine3DRadSpace::Objects::IObject
	{
	public:
		/// <summary>
		/// Main constructor.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="enabled">Enables physics at startup?</param>
		/// <param name="tag">String tag</param>
		/// <param name="gravity">Gravitatioal acceleration</param>
		GForce(
			const std::string& name = "GForce",
			bool enabled = true,
			const Math::Vector3& gravity = Math::Vector3(0, -9.81f, 0)
		);

		GForce(GForce&&) noexcept = default;
		GForce& operator=(GForce&&) noexcept = default;

		/// <summary>
		/// World wide gravitation acceleration in m/s^2.
		/// </summary>
		Math::Vector3 Gravity;

		/// <summary>
		/// Requests the Game class to initialize physics.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing. From IObject
		/// </summary>
		/// <param name="keyboard">Not used.</param>
		/// <param name="mouse">Not used.</param>
		/// <param name="dt">Not used.</param>
		void Update() override;
		/// <summary>
		/// Not used. From IObject
		/// </summary>
		/// <param name="content">Not used.</param>
		void Load() override;
		/// <summary>
		/// Not used. From IObject.
		/// </summary>
		/// <param name="content">Not used.</param>
		/// <param name="path">Not used.</param>
		void Load(const std::filesystem::path& path);

		/// <summary>
		/// Returns unique identifier used for serialization.
		/// </summary>
		/// <returns></returns>
		Reflection::UUID GetUUID() const noexcept override;

		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}

REFL_FWD(GForce)