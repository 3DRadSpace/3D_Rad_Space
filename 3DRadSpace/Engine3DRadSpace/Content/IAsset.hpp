#pragma once
#include "../GraphicsDevice.hpp"

namespace Engine3DRadSpace::Content
{
	class IAsset
	{
		unsigned _id;
	public:
		unsigned ID();
		std::string Name;
		std::string Path;

		virtual void *Get() = 0;
		virtual ~IAsset() = default;

		friend class ContentManager;
	};

	template<typename T>
	concept AssetType = requires(GraphicsDevice * dummy, const std::string &path)
	{
		T(dummy, path);
	};
}