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
		template<typename T>
		void AddService(T* service)
		{
			_services[typeid(T)] = service;
		}

		/// <summary>
		/// Gets the service of the given type. If the service is not found, nullptr is returned.
		/// </summary>
		/// <param name="type">Type of the service to get.</param>
		/// <returns>Pointer to the service of the given type, or nullptr if not found.</returns>
		IService* GetService(const std::type_index &type);

		/// <summary>
		///	Gets the service of type T. If the service is not found, nullptr is returned.
		/// </summary>
		/// <typeparam name="T">Type of the service to get.</typeparam>
		/// <param name="dummy">A dummy parameter to deduce the type T.</param>
		/// <returns>Pointer to the service of type T, or nullptr if not found.</returns>
		template<typename T>
		T* GetService(Tag<T> dummy)
		{
			(void)dummy;
			return static_cast<T*>(GetService(typeid(T)));
		}

		/// <summary>
		/// Requires a service of the given type. If the service is not found, it is attempted to be created.
		/// </summary>
		/// <param name="type">Type of the service to require.</param>
		/// <returns>Pointer to the service of the given type.</returns>
		virtual IService* RequireService(const std::type_index& type);

		/// <summary>
		/// Requires a service of type T. If the service is not found, it is attempted to be created.
		/// </summary>
		/// <typeparam name="T">Type of the service to require.</typeparam>
		/// <returns>Pointer to the service of type T.</returns>
		template<typename T>
		T* RequireService(Tag<T> dummy)
		{
			return static_cast<T*>(RequireService(typeid(T)));
		}

		virtual void Exit() = 0;

		std::unordered_map<std::type_index, IService*>::iterator begin();
		std::unordered_map<std::type_index, IService*>::iterator end();

		virtual bool WasInitialized() const noexcept = 0;
		virtual bool WasLoaded() const noexcept = 0;
		virtual bool IsEditor() const noexcept = 0;

		virtual void AppendScene(const std::filesystem::path& path) = 0;

		virtual ~IGame() = default;
	};
}