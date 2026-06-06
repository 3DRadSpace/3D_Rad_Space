#pragma once
#include "IGPUMultiBuffer.hpp"
#include "../Math/Point.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT ITexture2D : public IGPUMultiBuffer
	{
	protected:
		ITexture2D() = default;

		ITexture2D(const ITexture2D&) = delete;
		ITexture2D& operator=(const ITexture2D&) = delete;

		ITexture2D(ITexture2D&&) noexcept = default;
		ITexture2D& operator=(ITexture2D&&) noexcept = default;
	public:
		virtual Math::Point Size() const noexcept = 0;

		virtual unsigned Width() const noexcept = 0;
		virtual unsigned Height() const noexcept = 0;

		virtual void* GetViewHandle() const noexcept = 0;

		[[nodiscard]] virtual std::unique_ptr<ITexture2D> CreateStaging() = 0;
	
		virtual void SaveToFile(const std::filesystem::path& path) = 0;

		virtual ~ITexture2D() override = default;
	};
}