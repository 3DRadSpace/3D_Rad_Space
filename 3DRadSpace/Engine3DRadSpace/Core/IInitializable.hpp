#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Type for objects that require explicit initialization.
	/// </summary>
	class E3DRSP_CORE_EXPORT IInitializable
	{
	protected:
		IInitializable() = default;
	
		IInitializable(const IInitializable&) noexcept = default;
		IInitializable& operator=(const IInitializable&) noexcept = default;

		IInitializable(IInitializable&&) noexcept = default;
		IInitializable& operator=(IInitializable&&) noexcept = default;
	public:
		/// <summary>
		/// Initialization method.
		/// </summary>
		virtual void Initialize() = 0;
		virtual ~IInitializable() = default;
	};
}