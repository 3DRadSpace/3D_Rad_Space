#pragma once
#include "../Core/IService.hpp"
#include "Effect.hpp"
#include "IShader.hpp"

namespace Engine3DRadSpace
{
	class IGame;
}

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	///	Manages all Effect and IShader instances that exist in the application. 
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT EffectManager : public IService
	{
		IGame* _game;

		std::unordered_map<std::string, std::unique_ptr<Effect>> _effects;
		std::unordered_map<std::string, std::unique_ptr<IShader>> _shaders;
	public:
		/// <summary>
		/// Constructs an EffectManager instance.
		/// </summary>
		EffectManager();

		EffectManager(const EffectManager&) = delete;
		EffectManager(EffectManager&&) = delete;

		EffectManager& operator=(const EffectManager&) = delete;
		EffectManager& operator=(EffectManager&) = delete;

		/// <summary>
		/// Adds an Effect instance to the manager with the specified name.
		/// </summary>
		/// <param name="name">The name of the Effect instance.</param>
		/// <param name="effect">The Effect instance to add.</param>
		/// <returns>The added Effect instance.</returns>
		Effect* Add(const std::string& name, std::unique_ptr<Effect>&& effect);
		/// <summary>
		///	Adds an IShader instance to the manager with the specified name.
		/// </summary>
		/// <param name="name">The name of the IShader instance.</param>
		/// <param name="shader">The IShader instance to add.</param>
		/// <returns>The added IShader instance.</returns>
		IShader* Add(const std::string& name, std::unique_ptr<IShader>&& shader);
		/// <summary>
		///	Gets the effect that has the specified name.
		/// </summary>
		/// <param name="name">Identifier</param>
		/// <returns>The Effect instance with the specified name, or nullptr if not found.</returns>
		Effect* GetEffect(const std::string& name);
		/// <summary>
		///	Gets the shader that has the specified name.
		/// </summary>
		/// <param name="name">Identifier</param>
		/// <returns>The IShader instance with the specified name, or nullptr if not found.</returns>
		IShader* GetShader(const std::string& name);

		~EffectManager() override = default;
	};
}