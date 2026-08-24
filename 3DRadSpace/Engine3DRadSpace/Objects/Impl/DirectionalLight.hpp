#pragma once
#include "../IObject.hpp"
#include "../../Graphics/Rendering/DirectionalLight.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a directional light object in the scene.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT DirectionalLight : public IObject
	{
		Graphics::Rendering::DirectionalLight* _light = nullptr;
		bool _temporaryPointer = false;
	public:
		/// <summary>
		/// DirectionalLight complete constructor.
		/// </summary>
		/// <param name="name">Name of this object</param>
		/// <param name="visible">Whether the light is visible</param>
		/// <param name="direction">Direction of the light</param>
		/// <param name="lightColor">Color of the light</param>
		/// <param name="ambientColor">Ambient color of the light</param>
		/// <param name="intensity">Intensity of the light</param>
		explicit DirectionalLight(
			const std::string& name = "DirectionalLight",
			bool visible = true,
			const Math::Vector3& direction = Math::Vector3(0.0f, -1.0f, 0.0f),
			const Math::Color& lightColor = Math::Color(1.0f, 1.0f, 1.0f),
			const Math::Color& ambientColor = Math::Color(0.1f, 0.1f, 0.1f),
			float intensity = 1.0f
		);

		/// <summary>
		/// Gets the directional light referenced by this object.
		/// </summary>
		/// <returns>Reference to the directional light</returns>
		Graphics::Rendering::DirectionalLight* GetLight() const noexcept;
		/// <summary>
		/// Sets the light direction.
		/// </summary>
		/// <param name="direction">Light direction</param>
		void SetLightDir(const Math::Vector3& direction) noexcept;
		/// <summary>
		/// Sets the light color.
		/// </summary>
		/// <param name="color">Light color</param>
		void SetLightColor(const Math::Color& color) noexcept;
		/// <summary>
		/// Sets the ambient color.
		/// </summary>
		/// <param name="color">Ambient color</param>
		void SetAmbientColor(const Math::Color& color) noexcept;
		/// <summary>
		/// Sets the light intensity.
		/// </summary>
		/// <param name="intensity">Light intensity</param>
		void SetIntensity(float intensity) noexcept;
		/// <summary>
		/// Gets the light direction.
		/// </summary>
		/// <returns>Light direction</returns>
		Math::Vector3 GetLightDir() const noexcept;
		/// <summary>
		/// Gets the light color.
		/// </summary>
		/// <returns>Light color</returns>
		Math::Color GetLightColor() const noexcept;
		/// <summary>
		/// Gets the ambient color.
		/// </summary>
		/// <returns>Ambient color</returns>
		Math::Color GetAmbientColor() const noexcept;
		/// <summary>
		/// Gets the light intensity.
		/// </summary>
		/// <returns>Light intensity</returns>
		float GetIntensity() const noexcept;
		/// <summary>
		/// Syncronises all the properties of this object with the underlying directional light.
		/// </summary>
		void Sync() noexcept;
		/// <summary>
		/// Initializes the directional light object.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Calls Sync().
		/// </summary>
		void Update() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="path">Path to the file</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		///	Gets the UUID of the DirectionalLight class type.
		/// </summary>
		/// <returns>DirectionalLight UUID</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Gets the gizmo associated with this object.
		/// </summary>
		/// <returns>Gizmo associated with this object</returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};

}

REFL_FWD(DirectionalLight);