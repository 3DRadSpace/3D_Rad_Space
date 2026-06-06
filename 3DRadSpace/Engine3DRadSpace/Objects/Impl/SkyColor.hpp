#pragma once
#include "../IObject2D.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT SkyColor : public IObject
	{
	public:
		SkyColor(
			const std::string& name ="SkyColor", 
			bool enabled = true, 
			Math::Color color = Math::Colors::Black
		);

		SkyColor(SkyColor&&) noexcept = default;
		SkyColor& operator=(SkyColor&&) noexcept = default;

		Math::Color Colour;

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

	};
}

REFL_FWD(SkyColor)