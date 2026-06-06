#pragma once
#include "../IObject.hpp"
#include "../../Math/Point.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class SettingsManager : public IObject
	{
	public:
		SettingsManager(
			const std::string& name = "SettingsManager",
			const Math::Point& screenRes = Math::Point(800, 600),
			bool vsyncEnabled = true,
			bool fullscreenEnabled = false
		);

		SettingsManager(SettingsManager&&) noexcept = default;
		SettingsManager& operator=(SettingsManager&&) noexcept = default;

		Math::Point Resolution;
		bool VSyncEnabled;
		bool FullscreenEnabled;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;

		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}

REFL_FWD(SettingsManager)