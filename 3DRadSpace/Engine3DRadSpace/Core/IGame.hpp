#pragma once
#include "Libs.hpp"
#include "IService.hpp"
#include "Tag.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Base interface for a game class.
	/// </summary>
	class E3DRSP_CORE_EXPORT IGame
	{
	protected:
		std::unordered_map<std::type_index, IService*> _services;

		IGame() = default;

		IGame(const IGame&) = delete;
		IGame& operator=(const IGame&) = delete;

		IGame(IGame&&) noexcept = default;
		IGame& operator=(IGame&&) noexcept = default;
	public:
		/// <summary>
		/// Adds an service to this game. The service must be derived from IService.
		/// </summary>
		/// <typeparam name="S">Type of the service to add.</typeparam>
		/// <param name="service">Pointer to the service to add.</param>
		template<Service S>
		void AddService(S* service)
		{
			static_cast<IService*>(service)->_owner = this;
			_services[typeid(S)] = service;
		}

		/// <summary>
		/// Gets the service of the given type. If the service is not found, nullptr is returned.
		/// </summary>
		/// <param name="type">Type of the service to get.</param>
		/// <returns>Pointer to the service of the given type, or nullptr if not found.</returns>
		IService* GetService(const std::type_index &type);

		/// <summary>
		///	Gets the service of type S. If the service is not found, nullptr is returned.
		/// </summary>
		/// <typeparam name="S">Type of the service to get.</typeparam>
		/// <param name="dummy">A dummy parameter to deduce the type S.</param>
		/// <returns>Pointer to the service of type S, or nullptr if not found.</returns>
		template<Service S>
		S* GetService(Tag<S	> dummy)
		{
			(void)dummy;
			return static_cast<S*>(GetService(typeid(S)));
		}

		/// <summary>
		/// Requires a service of the given type. If the service is not found, it is attempted to be created.
		/// </summary>
		/// <param name="type">Type of the service to require.</param>
		/// <returns>Pointer to the service of the given type.</returns>
		virtual IService* RequireService(const std::type_index& type);

		/// <summary>
		/// Requires a service of type S. If the service is not found, it is attempted to be created.
		/// </summary>
		/// <typeparam name="S">Type of the service to require.</typeparam>
		/// <returns>Pointer to the service of type S.</returns>
		template<Service S>
		S* RequireService(Tag<S> dummy)
		{
			return static_cast<S*>(RequireService(typeid(S)));
		}

		/// <summary>
		/// Exits the game.
		/// </summary>
		virtual void Exit() = 0;

		/// <summary>
		/// Begin iterator for services in the game.
		/// </summary>
		/// <returns>_services.begin()</returns>
		std::unordered_map<std::type_index, IService*>::iterator begin();
		/// <summary>
		///	End iterator for services in the game.
		/// </summary>
		/// <returns>_services.end()</returns>
		std::unordered_map<std::type_index, IService*>::iterator end();

		/// <summary>
		/// Was ::Initialized() called on this instance?
		/// </summary>
		/// <returns>Was ::Initialized() called on this instance.</returns>
		virtual bool WasInitialized() const noexcept = 0;
		/// <summary>
		/// Was ::Load() called on this instance?
		/// </summary>
		/// <returns>Was ::Load() called on this instance.</returns>
		virtual bool WasLoaded() const noexcept = 0;
		/// <summary>
		/// Is this game instance an editor?
		/// </summary>
		/// <returns>True if this instance is an editor.</returns>
		virtual bool IsEditor() const noexcept = 0;
		///<summary>
		/// Appends a scene to the game.
		/// </summary>
		/// <param name="path">Path to the scene to append.</param>
		virtual void AppendScene(const std::filesystem::path& path) = 0;

		virtual ~IGame() = default;
	};
}