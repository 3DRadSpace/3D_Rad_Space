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
		virtual size_t ReadData(size_t subResource, void** data) = 0;
		virtual void SetData(size_t subResource, void* data, size_t buffSize) = 0;
		virtual void EndRead(size_t subResource) = 0;

		template<typename T>
		void SetData(size_t subResource, std::span<T> data)
		{
			SetData(subResource, &data[0], data.size_bytes());
		}
	};
}