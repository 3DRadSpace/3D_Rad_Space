#pragma once
#include <string>

namespace Engine3DRadSpace::Logging
{
	/// <summary>
	/// Replaces std::exception.
	/// </summary>
	class Exception
	{
	protected:
		std::string str;
	public:
		Exception(const std::string &err);
		virtual std::string &What();
		virtual ~Exception() = default;
	};
}

