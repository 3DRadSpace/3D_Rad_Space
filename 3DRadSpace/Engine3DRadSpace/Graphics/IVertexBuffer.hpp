#pragma once
#include "IGPUBuffer.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IVertexBuffer : public IGPUBuffer
	{
	protected:
		IVertexBuffer() = default;

		IVertexBuffer(const IVertexBuffer&) = delete;
		IVertexBuffer& operator=(const IVertexBuffer&) = delete;

		IVertexBuffer(IVertexBuffer&&) noexcept = default;
		IVertexBuffer& operator=(IVertexBuffer&&) noexcept = default;
	public:
		virtual size_t TotalSize() const noexcept = 0;
		virtual size_t StructSize() const noexcept = 0;
		virtual size_t NumVertices() const noexcept = 0;

		[[nodiscard]] virtual std::unique_ptr<IVertexBuffer> CreateStaging() = 0;
	};
}