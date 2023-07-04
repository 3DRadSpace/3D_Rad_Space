#pragma once
#include "../GraphicsDevice.hpp"

namespace Engine3DRadSpace::Content
{
	class DLLEXPORT IAsset
	{
		unsigned _id = 0;
	public:
		unsigned ID();
		std::string Name;
		std::string Path;

		IAsset() = default;

		IAsset(IAsset &) = default;
		IAsset(IAsset &&) noexcept = default;

		IAsset &operator=(IAsset &) = default;
		IAsset &operator=(IAsset &&) noexcept = default;

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