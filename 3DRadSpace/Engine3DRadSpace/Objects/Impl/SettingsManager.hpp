#pragma once
#include "../IObject.hpp"
#include "../../Math/Point.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a manager for game settings.
	/// </summary>
	class SettingsManager : public IObject
	{
	public:
		/// <summary>
		///	Complete SettingsManager constructor.
		/// </summary>
		/// <param name="name">Name of this object</param>
		/// <param name="screenRes">Initial screen resolution</param>
		/// <param name="vsyncEnabled">Is VSync enabled</param>
		/// <param name="fullscreenEnabled">Is fullscreen enabled</param>
		SettingsManager(
			const std::string& name = "SettingsManager",
			const Math::Point& screenRes = Math::Point(800, 600),
			bool vsyncEnabled = true,
			bool fullscreenEnabled = false
		);

		SettingsManager(SettingsManager&&) noexcept = default;
		SettingsManager& operator=(SettingsManager&&) noexcept = default;
		/// <summary>
		/// Backbuffer resolution.
		/// </summary>
		Math::Point Resolution;
		/// <summary>
		/// Enable vertical retrace?
		/// </summary>
		bool VSyncEnabled;
		/// <summary>
		/// Enable fullscreen?
		/// </summary>
		bool FullscreenEnabled;
		/// <summary>
		/// Applies the settings.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="path">unused.</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Does nothing. Use Initiailze() to apply settings.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Gets the UUID of SettingsManager class type.
		/// </summary>
		/// <returns>{88C432AA-2376-49CB-82A4-DF37E5D2F5A5}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Returns a null gizmo.
		/// </summary>
		/// <returns>null gizmo</returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}

REFL_FWD(SettingsManager)