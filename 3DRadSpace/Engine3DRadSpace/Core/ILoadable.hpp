#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Interface for objects that manage assets that exist on the filesystem.
	/// </summary>
	class E3DRSP_CORE_EXPORT ILoadable
	{
	protected:
		ILoadable() = default;

		ILoadable(const ILoadable&) noexcept = default;
		ILoadable& operator=(const ILoadable&) noexcept = default;

		ILoadable(ILoadable&&) noexcept = default;
		ILoadable& operator=(ILoadable&&) noexcept = default;
	public:
		/// <summary>
		/// Loads object's assets.
		/// </summary>
		virtual void Load() = 0;
		/// <summary>
		/// Reloads assets from another path. The initial underlying asset will not be replaced in the content manager.
		/// </summary>
		/// <param name="path">Specified asset path</param>
		virtual void Load(const std::filesystem::path& path) = 0;
		virtual ~ILoadable() = default;
	};
}