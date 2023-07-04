#pragma once
#include <string>
#include "../Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	/// <summary>
	/// Replaces std::exception.
	/// </summary>
	class DLLEXPORT Exception
	{
	protected:
		std::string _str;
	public:
		Exception(const std::string &err);
		virtual std::string &What();
		virtual ~Exception() = default;
	};
}

