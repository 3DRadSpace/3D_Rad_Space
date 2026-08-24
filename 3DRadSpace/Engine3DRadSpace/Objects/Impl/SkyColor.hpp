#pragma once
#include "../IObject2D.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents an object that sets the backbuffer clear color. Can be used as an trivial alternative to the Skybox object.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT SkyColor : public IObject
	{
	public:
		/// <summary>
		/// Complete SkyColor constructor.
		/// </summary>
		/// <param name="name"></param>
		/// <param name="enabled"></param>
		/// <param name="color"></param>
		SkyColor(
			const std::string& name ="SkyColor", 
			bool enabled = true, 
			Math::Color color = Math::Colors::Black
		);

		SkyColor(SkyColor&&) noexcept = default;
		SkyColor& operator=(SkyColor&&) noexcept = default;
		/// <summary>
		/// Backbuffer clear color.
		/// </summary>
		Math::Color Colour;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Gets the UUID for the SkyColor class.
		/// </summary>
		/// <returns>{EEA241C5-99C5-4A41-9E65-F673888CEBC4}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Returns an associated gizmo for this object that allows updating.
		/// </summary>
		/// <returns></returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;

	};
}

REFL_FWD(SkyColor)