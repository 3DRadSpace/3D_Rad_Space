#pragma once
#include "../IObject3D.hpp"
#include "../Math/Math.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class DLLEXPORT Camera : public IObject3D
	{
	public:
		Camera(const std::string& name = "Camera", const std::string& tag = "...", bool visible = true,
		       Math::Vector3 pos = Math::Vector3::Zero(),
		       Math::Vector3 look_at = Math::Vector3::UnitZ(),
		       Math::Vector3 up = Math::Vector3::UnitY(),
			float aspectRatio = 4.0f / 3.0f, float fov = Math::ToRadians(65.0f), float npd = 0.01f, float fpd = 500.0f);

		Math::Vector3 UpwardsDir;

		float AspectRatio;
		float FieldOfView;
		float NearPlaneDistance;
		float FarPlaneDistance;

		enum class CameraMode
		{
			UseRotation,
			UseLookAtCoordinates,
		} LookMode;

		Math::Vector3 LookAt;

		virtual void Initialize() override;
		virtual void Load(Content::ContentManager *content) override;
	
		virtual void EditorInitialize() override;
		virtual void EditorLoad(Content::ContentManager *content) override;

		/// <summary>
		/// Sets the view and projection matrices.
		/// </summary>
		/// <param name="view">View matrix reference</param>
		/// <param name="projection">Projection matrix reference</param>
		/// <param name="dt">Delta time, not used.</param>
		virtual void Draw(
			Math::Matrix4x4& view,
			Math::Matrix4x4& projection,
			double dt) override;

		/// <summary>
		/// Not used.
		/// </summary>
		/// <param name="keyboard">Keyboard reference</param>
		/// <param name="mouse">Mouse reference</param>
		/// <param name="dt">Delta-time</param>
		virtual void Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt) override;

		virtual Math::Matrix4x4 GetModelMartix() override;
		virtual void EditorDraw(
			const Math::Matrix4x4& view,
			const Math::Matrix4x4& projection,
			double dt,
			bool selected
		) override;

		virtual std::optional<float> Intersects(const Math::Ray &r) override;

		virtual Reflection::UUID GetUUID() override;

		virtual ~Camera() = default;
	};
}

REFL_DEF(Camera)