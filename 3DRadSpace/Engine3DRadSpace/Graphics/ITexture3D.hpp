#pragma once
#include "IGPUMultiBuffer.hpp"
#include "../Math/UPoint3.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT ITexture3D : public IGPUMultiBuffer
	{
	protected:
		ITexture3D() = default;

		ITexture3D(const ITexture3D&) = delete;
		ITexture3D& operator=(const ITexture3D&) = delete;

		ITexture3D(ITexture3D&&) noexcept = default;
		ITexture3D& operator=(ITexture3D&&) noexcept = default;
	public:
		virtual Math::UPoint3 Size() const noexcept = 0;

		virtual unsigned Width() const noexcept = 0;
		virtual unsigned Height() const noexcept = 0;
		virtual unsigned Depth() const noexcept = 0;

		virtual void* GetViewHandle() const noexcept = 0;

		[[nodiscard]] virtual std::unique_ptr<ITexture3D> CreateStaging() = 0;

		virtual ~ITexture3D() override = default;
	};
}