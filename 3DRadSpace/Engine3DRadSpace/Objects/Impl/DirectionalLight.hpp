#pragma once
#include "../IObject.hpp"
#include "../../Graphics/Rendering/DirectionalLight.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT DirectionalLight : public IObject
	{
		Graphics::Rendering::DirectionalLight* _light = nullptr;
		bool _temporaryPointer = false;
	public:
		DirectionalLight(
			const std::string& name = "DirectionalLight",
			bool visible = true,
			const Math::Vector3& direction = Math::Vector3(0.0f, -1.0f, 0.0f),
			const Math::Color& lightColor = Math::Color(1.0f, 1.0f, 1.0f),
			const Math::Color& ambientColor = Math::Color(0.1f, 0.1f, 0.1f),
			float intensity = 1.0f
		);

		Graphics::Rendering::DirectionalLight* GetLight() const noexcept;

		void SetLightDir(const Math::Vector3& direction) noexcept;
		void SetLightColor(const Math::Color& color) noexcept;
		void SetAmbientColor(const Math::Color& color) noexcept;
		void SetIntensity(float intensity) noexcept;

		Math::Vector3 GetLightDir() const noexcept;
		Math::Color GetLightColor() const noexcept;
		Math::Color GetAmbientColor() const noexcept;
		float GetIntensity() const noexcept;

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		Reflection::UUID GetUUID() const noexcept override;

		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};

}

REFL_FWD(DirectionalLight);