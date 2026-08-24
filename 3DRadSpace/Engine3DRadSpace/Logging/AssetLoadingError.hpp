#pragma once
#include "Exception.hpp"
#include "../Core/Tag.hpp"

namespace Engine3DRadSpace
{
	namespace Logging
	{
		/// <summary>
		/// Represents an exception that is thrown when an asset fails to load.
		/// </summary>
		class E3DRSP_LOGGING_EXPORT AssetLoadingError : public Exception
		{
		public:
			template<typename T>
			AssetLoadingError(Tag<T> tag, const std::filesystem::path &file, const std::string &details) :
				Exception( "Failed to load " + std::string(typeid(T).name()) + " from file " + file.string() + "\r\n" + details)
			{
			}

			~AssetLoadingError() override = default;
		};
	}
}