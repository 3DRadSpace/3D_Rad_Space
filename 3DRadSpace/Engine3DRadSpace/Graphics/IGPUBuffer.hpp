#pragma once
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	///	Represents an polymorphic interface for classes that own GPU buffer handles.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT IGPUBuffer : public IGPUResource
	{
	protected:
		IGPUBuffer() = default;

		IGPUBuffer(const IGPUBuffer&) = delete;
		IGPUBuffer& operator=(const IGPUBuffer&) = delete;

		IGPUBuffer(IGPUBuffer&&) noexcept = default;
		IGPUBuffer& operator=(IGPUBuffer&&) noexcept = default;
	public:
		/// <summary>
		/// Maps and reads the data from the GPU buffer.
		/// </summary>
		/// <param name="data">A pointer to the data buffer.</param>
		/// <returns>The size of the data read.</returns>
		virtual size_t ReadData(void **data) = 0;
		/// <summary>
		/// Maps and writes the data to the GPU buffer. After the write operation, the buffer is immediately unmapped.
		/// </summary>
		/// <param name="data">A pointer to the data buffer.</param>
		/// <param name="buffSize">The size of the data buffer.</param>
		virtual void SetData(void *data, size_t buffSize) = 0;
		/// <summary>
		/// Ends the read operation on the GPU buffer.
		/// </summary>
		virtual void EndRead() = 0;

		/// <summary>
		/// Sets the data to the GPU buffer as if it is an array of type T.
		/// </summary>
		/// <typeparam name="T">The type of the elements in the span.</typeparam>
		/// <param name="data">A span containing the data to set.</param>
		template<typename T>
		void SetData(std::span<T> data)
		{
			SetData(&data[0], data.size_bytes());
		}

		~IGPUBuffer() override = default;
	};
}