#pragma once
#include <typeinfo>
#include "Exception.hpp"

namespace Engine3DRadSpace
{
	template<typename T>
	struct Tag
	{
	};

	namespace Logging
	{
		class ResourceLoadingError : public Exception
		{
		public:
			template<typename T>
			ResourceLoadingError(Tag<T> tag, const std::string &file, const std::string &details) :
				Exception( "Failed to load " + std::string(typeid(T).name()) + " from file" + file + "\r\n" + details)
			{
			}
		};
	}
}