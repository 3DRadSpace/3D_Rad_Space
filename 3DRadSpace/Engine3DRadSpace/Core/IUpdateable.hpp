#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Interface type for objects that can be updated every frame.
	/// </summary>
	class E3DRSP_CORE_EXPORT IUpdateable
	{
	protected:
		IUpdateable() = default;

		IUpdateable(const IUpdateable&) noexcept = default;
		IUpdateable& operator=(const IUpdateable&) noexcept = default;

		IUpdateable(IUpdateable&&) noexcept = default;
		IUpdateable& operator=(IUpdateable&&) noexcept = default;
	public:
		/// <summary>
		/// Update function.
		/// </summary>
		virtual void Update() = 0;
		inline virtual ~IUpdateable() = default;
	};
}