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
		/// <summary>
		/// Complete fog constructor.
		/// </summary>
		/// <param name="name">Object name</param>
		/// <param name="enabled">Is the fog enabled</param>
		/// <param name="begin">Fog start distance</param>
		/// <param name="end">Fog end distance</param>
		/// <param name="color">Fog color</param>
		Fog(
			const std::string& name = "Fog", 
			bool enabled = true,
			float begin = 200.0f,
			float end = 500.0f,
			Math::Color color = Math::Colors::White
		);
		/// <summary>
		///	Default move constructor for Fog.
		/// </summary>
		Fog(Fog&&) = default;
		/// <summary>
		///	Default move assignment operator for Fog.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		Fog& operator=(Fog&&) = default;
		/// <summary>
		/// Fog start distance in meters.
		/// </summary>
		float FogBegin;
		/// <summary>
		/// Fog end distance in meters.
		/// </summary>
		float FogEnd;
		/// <summary>
		/// Fog color.
		/// </summary>
		Math::Color FogColor;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Retrieves the fog effect from the graphics device and sets its parameters.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Same as Load() without arguments.
		/// </summary>
		/// <param name="path">unused.</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Synchronizes the fog effect with the current parameters. This is called every frame.
		/// </summary>
		void Update() override;
		/// <summary>
		///	Returns the unique identifier for the Fog class.
		/// </summary>
		/// <returns>{57299A03-31EA-43D2-A58E-C1F865E1EF85}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		///	Returns the gizmo associated with this object.
		/// </summary>
		/// <returns></returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~Fog() override;
	};
}

REFL_FWD(Fog)