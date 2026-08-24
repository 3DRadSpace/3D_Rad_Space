#pragma once
#include "IPhysicsObject.hpp"
#include "../../Objects/Impl/FreeCam.hpp"
#include "../ICharacterController.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// Represents an first person character controller that can be used to control a character in a 3D world.
	/// </summary>
	class E3DRSP_PHYSICS_OBJ_EXPORT FPCharacter : public Engine3DRadSpace::Objects::FreeCam
	{
	protected:
		IPhysicsEngine* _physics;
		std::unique_ptr<ICharacterController> _controller;
	public:
		/// <summary>
		/// Complete constructor.
		/// </summary>
		/// <param name="name">Name of the character</param>
		/// <param name="visible">Indicates whether the character is visible</param>
		/// <param name="pos">Initial position of the character</param>
		/// <param name="rotation">Initial rotation of the character</param>
		/// <param name="up">Up direction of the character</param>
		/// <param name="aspectRatio">Aspect ratio of the character's view</param>
		/// <param name="fov">Field of view of the character's view</param>
		/// <param name="npd">Near plane distance of the character's view</param>
		/// <param name="fpd">Far plane distance of the character's view</param>
		FPCharacter(
			const std::string& name = "FPCharacter",
			bool visible = true,
			const Math::Vector3& pos = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& up = Math::Vector3::UnitY(),
			float aspectRatio = 4.0f / 3.0f,
			float fov = Math::ToRadians(65.0f),
			float npd = 0.01f,
			float fpd = 500.0f
		);

		FPCharacter(FPCharacter&&) noexcept = default;
		FPCharacter& operator=(FPCharacter&&) noexcept = default;
		/// <summary>
		/// Radius of the character's capsule collider. Default is 0.5f.
		/// </summary>
		float Radius = 0.5f;
		/// <summary>
		/// Height of the character's capsule collider. Default is 1.8f.
		/// </summary>
		float Height = 1.8f;
		/// <summary>
		/// Jump key.
		/// </summary>
		Input::Key Jump = Input::Key::Space;
		/// <summary>
		/// Jump power.
		/// </summary>
		float JumpPower = 1.0f;
		/// <summary>
		/// Retrieves relevant services.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Handles input and updates the character's physics state.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Updates the view and projection matrices.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Teleports the character to the specified position in world space.
		/// </summary>
		/// <param name="position">The position to teleport the character to.</param>
		void Teleport(const Math::Vector3& position);
		/// <summary>
		/// Teleports the character to the specified position and rotation in world space.
		/// </summary>
		/// <param name="position">The position to teleport the character to.</param>
		/// <param name="rotation">The rotation to set the character to.</param>	
		void Teleport(const Math::Vector3& position, const Math::Quaternion& rotation);
		/// <summary>
		/// Gets the underlying character controller used for physics interactions.
		/// </summary>
		/// <returns>The underlying character controller.</returns>
		ICharacterController* GetController() const noexcept;
		/// <summary>
		/// Gets the UUID of the FPCharacter object.
		/// </summary>
		/// <returns>{AC8F8DF7-80EC-4293-A78B-DE7F3FFFBF49}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Gets the view matrix of this FPCharacter.
		/// </summary>
		/// <returns></returns>
		Math::Matrix4x4 GetViewMatrix() const noexcept override;

		~FPCharacter() override = default;
	};
}

REFL_FWD(FPCharacter)