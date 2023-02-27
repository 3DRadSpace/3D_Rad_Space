#pragma once
#include "IObject.hpp"
#include "Math.hpp"

namespace Engine3DRadSpace::Objects
{
	class Camera : public IObject
	{
	public:
		Camera(const std::string& name = "Camera", const std::string& tag = "...", bool visible = true, 
			Engine3DRadSpace::Math::Vector3 pos = Engine3DRadSpace::Math::Vector3::Zero(),
			Engine3DRadSpace::Math::Vector3 look_at = Engine3DRadSpace::Math::Vector3::UnitZ(),
			Engine3DRadSpace::Math::Vector3 up = Engine3DRadSpace::Math::Vector3::UnitY(),
			float aspectRatio = 4.0f / 3.0f, float fov = Math::ToRadians(65.0f), float npd = 0.01f, float fpd = 500.0f);

		Engine3DRadSpace::Math::Vector3 UpwardsDir;

		float AspectRatio;
		float FieldOfView;
		float NearPlaneDistance;
		float FarPlaneDistance;

		void SetLookAt(const Engine3DRadSpace::Math::Vector3& lookAt);

		void Initialize() override;

		/// <summary>
		/// Sets the view and projection matrices.
		/// </summary>
		/// <param name="view">View matrix reference</param>
		/// <param name="projection">Projection matrix reference</param>
		/// <param name="dt">Delta time, not used.</param>
		void Draw(
			Engine3DRadSpace::Math::Matrix& view,
			Engine3DRadSpace::Math::Matrix& projection,
			double dt) override;

		/// <summary>
		/// Not used.
		/// </summary>
		/// <param name="keyboard">Keyboard reference</param>
		/// <param name="mouse">Mouse reference</param>
		/// <param name="dt">Delta-time</param>
		void Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt) override;

		void EditorDraw(
			const Engine3DRadSpace::Math::Matrix& view,
			const Engine3DRadSpace::Math::Matrix& projection,
			double dt
		);
	};
}