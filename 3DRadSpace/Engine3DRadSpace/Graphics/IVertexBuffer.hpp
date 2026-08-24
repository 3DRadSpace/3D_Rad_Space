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
		/// <summary>
		/// Gets the size of the vertex structure in bytes.
		/// </summary>
		/// <returns>Usually StructSize() * NumVertices()</returns>
		virtual size_t TotalSize() const noexcept = 0;
		/// <summary>
		/// Gets the vertex structure size.
		/// </summary>
		/// <returns>The size of the vertex structure in bytes.</returns>
		virtual size_t StructSize() const noexcept = 0;
		/// <summary>
		///	Gets the number of vertices in the vertex buffer.
		/// </summary>
		/// <returns>The number of vertices in the vertex buffer.</returns>
		virtual size_t NumVertices() const noexcept = 0;

		/// <summary>
		/// Creates a staging vertex buffer that can be used for CPU read/write operations.
		/// </summary>
		/// <returns>A unique pointer to the created staging vertex buffer.</returns>
		[[nodiscard]] virtual std::unique_ptr<IVertexBuffer> CreateStaging() = 0;
	};
}