#pragma once
#include "IAssetWrapper.hpp"
#include "../../Graphics/Model3D.hpp"

namespace Engine3DRadSpace
{
	class IService;
	namespace Internal
	{
		struct AssetUUIDReader;
	}

	namespace Content::Assets
	{
		/// <summary>
		/// Represents an 3D model asset.
		/// </summary>
		class E3DRSP_CONTENT_ASSETS_EXPORT ModelAsset final : public IAssetWrapper<Graphics::Model3D>
		{
			ModelAsset(Internal::AssetUUIDReader dummy);
		public:
			/// <summary>
			///	Constructs an ModelAsset.
			/// </summary>
			/// <param name="device">IGraphicsDevice instance</param>
			/// <param name="path">Path to the model file</param>
			ModelAsset(IService* device, const std::filesystem::path &path);

			/// <summary>
			/// Unique identifier for the ModelAsset type.
			/// </summary>
			/// <returns>UUID of the ModelAsset type</returns>
			Reflection::UUID GetUUID() const noexcept override;
			/// <summary>
			/// Refer to https://github.com/assimp/assimp/blob/master/doc/Fileformats.md for all supported file formats.
			/// </summary>
			/// <returns>File extension of the model asset</returns>
			const char* FileExtension() const noexcept override;

			/// <summary>
			/// Returns typeid(IGraphicsDevice)
			/// </summary>
			/// <returns>typeid(IGraphicsDevice)</returns>
			std::type_index InitializationService() const noexcept override;

			~ModelAsset() override = default;

			friend struct Internal::AssetUUIDReader;
		};
	}
}