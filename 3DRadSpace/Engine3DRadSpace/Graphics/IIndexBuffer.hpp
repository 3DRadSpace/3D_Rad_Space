#pragma once
#include "IGPUBuffer.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Interface for an index buffer.
	/// </summary>
	class IIndexBuffer : public IGPUBuffer
	{
	protected:
		IIndexBuffer() = default;

		IIndexBuffer(const IIndexBuffer&) = delete;
		IIndexBuffer& operator=(const IIndexBuffer&) = delete;

		IIndexBuffer(IIndexBuffer&&) noexcept = default;
		IIndexBuffer& operator=(IIndexBuffer&&) noexcept = default;
	public:
		/// <summary>
		///	Assigns the index buffer to the rendering pipeline.
		/// </summary>
		/// <param name="index">The index to set the buffer at.</param>
		virtual void Set(unsigned index) = 0;
		/// <summary>
		/// Gets the number of indices in the index buffer.
		/// </summary>
		/// <returns>The number of indices in the index buffer.</returns>
		virtual unsigned NumIndices() const noexcept = 0;

		/// <summary>
		/// Create a staging buffer from this index buffer. The staging buffer can be used to read data from the GPU.
		/// </summary>
		/// <returns>Unique pointer to the created staging index buffer.</returns>
		[[nodiscard]] virtual std::unique_ptr<IIndexBuffer> CreateStaging() = 0;

		~IIndexBuffer() override = default;
	};
}