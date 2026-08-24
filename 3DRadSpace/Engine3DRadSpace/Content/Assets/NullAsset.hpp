#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace::Internal
{
	struct AssetUUIDReader;
}

namespace Engine3DRadSpace::Content::Assets
{
	/// <summary>
	/// Represent a null asset.
	/// </summary>
	class E3DRSP_CONTENT_ASSETS_EXPORT NullAsset final: public IAsset
	{
		NullAsset(Internal::AssetUUIDReader dummy);
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		NullAsset() = default;
		/// <summary>
		///	Extended constructor.
		/// </summary>
		/// <param name="service">unused</param>
		/// <param name="dummy">unused</param>
		NullAsset(IService* service, const std::filesystem::path& dummy);

		NullAsset(NullAsset&&) noexcept= default;
		NullAsset& operator=(NullAsset&&) noexcept = default;

		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		///	Returns an filter that allows all file types.
		/// </summary>
		/// <returns>File extension filter</returns>
		const char* FileExtension() const noexcept override;
		/// <summary>
		/// Returns typeid(void)
		/// </summary>
		/// <returns>typeid(void)</returns>
		std::type_index InitializationService() const noexcept override;

		friend class Internal::AssetUUIDReader;
	};
}