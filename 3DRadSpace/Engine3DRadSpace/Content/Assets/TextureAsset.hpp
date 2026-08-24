#pragma once
#include "../IAsset.hpp"
#include "../../Graphics/ITexture2D.hpp"

namespace Engine3DRadSpace
{
	class IService;
	namespace Graphics
	{
		class ITexture2D;
	}
	namespace Internal
	{
		struct AssetUUIDReader;
	}

	namespace Content::Assets
	{
		/// <summary>
		/// Asset type for ITexture2D objects. This asset type is used to load textures from disk and manage their lifetime.
		/// </summary>
		class E3DRSP_CONTENT_ASSETS_EXPORT TextureAsset final : public IAsset
		{
			std::unique_ptr<Graphics::ITexture2D> _texture;

			TextureAsset(Internal::AssetUUIDReader dummy);
		public:
			/// <summary>
			/// Constructs an texture asset from a file path.
			/// </summary>
			/// <param name="device">IGraphicsDevice instance</param>
			/// <param name="path">Path to an image file</param>
			TextureAsset(IService* device, const std::filesystem::path& path);

			TextureAsset(const TextureAsset&) = delete;
			TextureAsset(TextureAsset&&) noexcept = default;

			TextureAsset& operator=(const TextureAsset&) = delete;
			TextureAsset& operator=(TextureAsset&&) noexcept = default;

			/// <summary>
			/// Returns an unique identifier for the asset type.
			/// </summary>
			/// <returns></returns>
			Reflection::UUID GetUUID() const noexcept override;
			/// <summary>
			///	Returns the file extension(s) used as a filter for the editor.
			/// </summary>
			/// <remarks>
			/// All supported image file types are bmp, dib, jpg, jpeg, gif, tiff, tif, png, dds.
			/// </remarks>
			/// <returns>A string containing the supported file extensions.</returns>
			const char* FileExtension() const noexcept override;
			/// <summary>
			/// Returns typeid(IGraphicsDevice)
			/// </summary>
			/// <returns></returns>
			std::type_index InitializationService() const noexcept override;

			/// <summary>
			/// Returns a pointer to the underlying ITexture2D object.
			/// </summary>
			/// <returns>A pointer to the underlying ITexture2D object.</returns>
			Graphics::ITexture2D* Get() const noexcept;

			~TextureAsset() override = default;

			friend class Internal::AssetUUIDReader;
		};
	}
}