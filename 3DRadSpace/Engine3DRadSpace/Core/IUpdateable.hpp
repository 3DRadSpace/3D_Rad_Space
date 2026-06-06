#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_CORE_EXPORT IUpdateable
	{
	protected:
		IUpdateable() = default;

		IUpdateable(const IUpdateable&) noexcept = default;
		IUpdateable& operator=(const IUpdateable&) noexcept = default;

		IUpdateable(IUpdateable&&) noexcept = default;
		IUpdateable& operator=(IUpdateable&&) noexcept = default;
	public:
		virtual void Update() = 0;
		inline virtual ~IUpdateable() = default;
	};
}