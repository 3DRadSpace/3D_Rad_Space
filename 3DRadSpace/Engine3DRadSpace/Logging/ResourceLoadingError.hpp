#pragma once
#include <typeinfo>
#include "Exception.hpp"
#include "../Tag.hpp"

namespace Engine3DRadSpace
{
	namespace Logging
	{
		class ResourceLoadingError : public Exception
		{
		public:
			template<typename T>
			ResourceLoadingError(Tag<T> tag, const std::filesystem::path &file, const std::string &details) :
				Exception( "Failed to load " + std::string(typeid(T).name()) + " from file" + file.string() + "\r\n" + details)
			{
			}
		};
	}
}