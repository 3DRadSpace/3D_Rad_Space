#pragma once
#include "../Reflection/UUID.hpp"
#include "../Core/IService.hpp"

namespace Engine3DRadSpace
{
	namespace Graphics
	{
		class IGraphicsDevice;
	}
	namespace Internal
	{
		struct AssetUUIDReader;
	}
}

namespace Engine3DRadSpace::Content
{
	/// <summary>
	/// Asset polymorphic base type.
	/// </summary>
	class E3DRSP_CONTENT_EXPORT IAsset
	{
	protected:
		IAsset() = default;

		IAsset(const IAsset&) = default;
		IAsset& operator=(const IAsset&) = default;

		IAsset(IAsset&&) noexcept = default;
		IAsset& operator=(IAsset&&) noexcept = default;
	public:
		/// <summary>
		/// Represents a unique identifier for the asset type.
		/// </summary>
		/// <returns></returns>
		virtual Reflection::UUID GetUUID() const noexcept = 0;
		/// <summary>
		/// File extension(s) used as a filter for the editor.
		/// </summary>
		/// <returns></returns>
		virtual const char* FileExtension() const noexcept = 0;

		/// <summary>
		/// Returns the type of the servive used to initialize this asset.
		/// </summary>
		virtual std::type_index InitializationService() const noexcept = 0;

		virtual ~IAsset() = default;
	};

	template<typename T>
	concept AssetType = std::is_base_of_v<IAsset, T> && std::is_constructible_v<T, IService*, const std::filesystem::path&>;
}