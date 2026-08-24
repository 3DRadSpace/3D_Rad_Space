#pragma once
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a base interface for GPU resources that have subresources.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT IGPUMultiBuffer : public IGPUResource
	{
	protected:
		IGPUMultiBuffer() = default;

		IGPUMultiBuffer(const IGPUMultiBuffer&) = delete;
		IGPUMultiBuffer& operator=(const IGPUMultiBuffer&) = delete;

		IGPUMultiBuffer(IGPUMultiBuffer&&) noexcept = default;
		IGPUMultiBuffer& operator=(IGPUMultiBuffer&&) noexcept = default;
	public:
		/// <summary>
		/// Reads the data of a subresource and returns the size of the data read.
		/// </summary>
		/// <param name="subResource">The index of the subresource to read.</param>
		/// <param name="data">A pointer to a pointer that will receive the address of the data.</param>
		/// <returns>The size of the data read.</returns>
		virtual size_t ReadData(size_t subResource, void** data) = 0;
		/// <summary>
		/// Sets the data of a subresource with the specified data and buffer size.
		/// </summary>
		/// <param name="subResource">The index of the subresource to set.</param>
		/// <param name="data">A pointer to the data to set.</param>
		/// <param name="buffSize">The size of the data in bytes.</param>
		virtual void SetData(size_t subResource, void* data, size_t buffSize) = 0;
		/// <summary>
		/// Unmaps the specified subresource after reading its data, indicating that the read operation is complete.
		/// </summary>
		/// <param name="subResource">The index of the subresource to unmap.</param>
		virtual void EndRead(size_t subResource) = 0;

		/// <summary>
		/// Reads the data of a subresource and returns it as a array of type T.
		/// </summary>
		/// <typeparam name="T">The type of the elements in the array.</typeparam>
		/// <param name="subResource">The index of the subresource to read.</param>
		/// <param name="data">A pointer to a pointer that will receive the address of the data.</param>
		template<typename T>
		void SetData(size_t subResource, std::span<T> data)
		{
			SetData(subResource, &data[0], data.size_bytes());
		}
	};
}