#pragma once
#include "..\IObject.hpp"
#include "..\..\Reflection\Reflection.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class LinearPixelFogEffect;
}

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// This object controls the Fog effect.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT Fog: public IObject
	{
	protected:
		::Engine3DRadSpace::Graphics::Rendering::LinearPixelFogEffect* _effect;
	public:
		Fog(
			const std::string& name = "Fog", 
			bool enabled = true,
			float begin = 200.0f,
			float end = 500.0f,
			Math::Color color = Math::Colors::White
		);

		Fog(Fog&&) = default;
		Fog& operator=(Fog&&) = default;

		float FogBegin;
		float FogEnd;
		Math::Color FogColor;

		void Initialize() override;

		void Load() override;
		void Load(const std::filesystem::path& path) override;

		void Update() override;

		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~Fog() override;
	};
}

REFL_FWD(Fog)