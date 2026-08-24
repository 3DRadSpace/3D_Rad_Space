#pragma once
#include "..\IObject2D.hpp"
#include "..\..\Reflection\Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	///	When triggered, loads another scene.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT ExitFade : public IObject2D
	{
		float _timer = 0.0f;
	public:
		/// <summary>
		/// Complete constructor for ExitFade.
		/// </summary>
		/// <param name="name">Object name</param>
		/// <param name="projectPath">Path to the project</param>
		/// <param name="fadeColor">Color of the fade</param>
		/// <param name="fadeTime">Duration of the fade</param>
		explicit ExitFade(
			const std::string& name = "ExitFade",
			const std::filesystem::path& projectPath = "",
			Math::Color fadeColor = Math::Colors::Black, 
			float fadeTime = 5.0f
		);
		/// <summary>
		/// Default copy constructor for ExitFade.
		/// </summary>
		ExitFade(ExitFade&&) noexcept = default;
		/// <summary>
		/// Default move assignment operator for ExitFade.
		/// </summary>
		ExitFade& operator=(ExitFade&&) noexcept = default;
		/// <summary>
		/// Path to the project to load when the fade is complete.
		/// </summary>
		std::string ProjectPath;
		/// <summary>
		///	Fade out color. The screen will fade to this color before loading the new scene.
		/// </summary>
		Math::Color FadeColor;
		/// <summary>
		/// How long does the fade out last in seconds.
		/// </summary>
		float FadeTime;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Draws the fade effect and updates the internal timer.
		/// </summary>
		void Draw2D() override;

		/// <summary>
		/// Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="path">unused</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		///	Gets the associated unique identifier for the ExitFade class.
		/// </summary>
		/// <returns></returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		///	Returns null.
		/// </summary>
		/// <returns>null gizmo</returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}

REFL_FWD(ExitFade)