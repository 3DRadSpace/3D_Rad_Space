#pragma once
#include "IAssetWrapper.hpp"
#include "../../Graphics/Font.hpp"

namespace Engine3DRadSpace
{
	namespace Internal
	{
		struct AssetUUIDReader;
	}

	namespace Content::Assets
	{
		class E3DRSP_CONTENT_ASSETS_EXPORT FontAsset final : public IAssetWrapper<Graphics::Font>
		{
			FontAsset(Internal::AssetUUIDReader dummy);
		public:
			/// <summary>
			/// Constructs an font asset
			/// </summary>
			/// <param name="device">IGraphicsDevice instance used to load the font</param>
			/// <param name="path">Path to the font file (ttf)</param>
			FontAsset(IService* device, const std::filesystem::path &path);

			/// <summary>
			/// UUID of the Font type. Used internally.
			/// </summary>
			/// <returns>UUID</returns>
			Reflection::UUID GetUUID() const noexcept override;
			/// <summary>
			/// Supported file types, used internally.
			/// </summary>
			/// <returns>Supported file types</returns>
			const char* FileExtension() const noexcept override;

			/// <summary>
			/// Returns typeid(IGraphicsDevice)
			/// </summary>
			/// <returns>typeid(IGraphicsDevice)</returns>
			std::type_index InitializationService() const noexcept override;

			~FontAsset() override = default;

			friend struct Internal::AssetUUIDReader;
		};
	}
}
