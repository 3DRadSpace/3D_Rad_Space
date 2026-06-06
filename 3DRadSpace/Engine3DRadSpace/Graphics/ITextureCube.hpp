#pragma once
#include "IGPUMultiBuffer.hpp"
#include "../Math/UPoint.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents an cubemap made of 6 2D textures.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ITextureCube : public IGPUMultiBuffer
	{
	protected:
		ITextureCube() = default;

		ITextureCube(const ITextureCube&) = delete;
		ITextureCube& operator=(const ITextureCube&) = delete;

		ITextureCube(ITextureCube&&) noexcept = default;
		ITextureCube& operator=(ITextureCube&&) noexcept = default;
	public:
		virtual Math::UPoint Size() const noexcept = 0;

		virtual unsigned Width() const noexcept = 0;
		virtual unsigned Height() const noexcept = 0;

		virtual void* GetViewHandle() const noexcept = 0;

		[[nodiscard]] virtual std::unique_ptr<ITextureCube> CreateStaging() = 0;

		virtual ~ITextureCube() override = default;
	};
}