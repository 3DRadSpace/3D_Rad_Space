#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	class IGame;

	/// <summary>
	/// Polymorphic base for all services used by the engine.
	/// </summary>
	class E3DRSP_CORE_EXPORT IService
	{
	protected:
		IGame* _owner = nullptr;

		IService();
		IService(IGame* owner);
		
		IService(const IService&) = delete;
		IService& operator=(const IService&) = delete;

		IService(IService&&) noexcept = default;
		IService& operator=(IService&&) noexcept = default;
	public:
		/// <summary>
		/// Gets the owner of this instance.
		/// </summary>
		/// <returns>IGame owner</returns>
		IGame* GetOwner() const noexcept;

		virtual ~IService() = default;

		friend class IGame;
	};

	/// <summary>
	/// Is S a service?
	/// </summary>
	template<typename S>
	concept Service = std::is_base_of_v<IService, S>;
}