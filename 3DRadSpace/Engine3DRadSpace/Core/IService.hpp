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
	public:
		void SetOwner(IGame* owner) noexcept;
		IGame* GetOwner() const noexcept;

		virtual ~IService() = default;
	};
}