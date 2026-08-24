#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Reflection
{
	#pragma warning(push)
	#pragma warning(disable:26495)
	/// <summary>
	/// Enumeration entry.
	/// </summary>
	struct EnumEntry
	{
		/// <summary>
		/// Visible name of this entry.
		/// </summary>
		std::string VisibleName;
		/// <summary>
		/// Value of this entry.
		/// </summary>
		int64_t Value;
	};
	#pragma warning(pop)
}