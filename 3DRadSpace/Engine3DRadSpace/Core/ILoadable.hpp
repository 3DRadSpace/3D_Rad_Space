#pragma once
#include "Libs.hpp"

namespace Engine3DRadSpace
{
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
		/// <param name="content"></param>
		virtual void Load() = 0;
		/// <summary>
		/// Reloads assets from an other path.
		/// </summary>
		/// <param name="content">Content manager used to load the asset(s).</param>
		/// <param name="path">Specified asset path</param>
		virtual void Load(const std::filesystem::path& path) = 0;
		virtual ~ILoadable() = default;
	};
}