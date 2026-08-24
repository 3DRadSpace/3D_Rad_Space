#pragma once
#include "../../Graphics/Primitives/CubeMapSkybox.hpp"
#include "IAssetWrapper.hpp"
#include "../../Core/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Content::Assets
{
	/// <summary>
	/// Represents an skybox asset, which is a wrapper around a CubeMapSkybox primitive.
	/// </summary>
	class E3DRSP_CONTENT_ASSETS_EXPORT SkyboxAsset : public IAssetWrapper<Graphics::Primitives::CubeMapSkybox>
	{
		Graphics::Primitives::CubeMapSkybox _loadCubeMap(Graphics::IGraphicsDevice *device, const std::filesystem::path& path);

		SkyboxAsset(Internal::AssetUUIDReader dummy);
	public:
		/// <summary>
		/// Constructs an instance of the SkyboxAsset class, loading the skybox from the specified path.
		/// </summary>
		/// <param name="device">The graphics device used to initialize the skybox.</param>
		/// <param name="path">The file path to the skybox texture.</param>
		SkyboxAsset(IService *device, const std::filesystem::path& path);

		SkyboxAsset(SkyboxAsset&&) noexcept = default;
		SkyboxAsset& operator=(SkyboxAsset&&) noexcept = default;

		/// <summary>
		/// Returns an unique identifier for the SkyboxAsset type.
		/// </summary>
		/// <returns></returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Returns an filter supporting *.skybox files and *.dds files.
		/// </summary>
		/// <returns></returns>
		const char* FileExtension() const noexcept override;
		/// <summary>
		/// Returns typeid(IGraphicsDevice), which is the service used to initialize the SkyboxAsset.
		/// </summary>
		/// <returns></returns>
		std::type_index InitializationService() const noexcept override;

		/// <summary>
		/// Destructor for the SkyboxAsset class.
		/// </summary>
		~SkyboxAsset() override = default;

		friend class Internal::AssetUUIDReader;
	};
}