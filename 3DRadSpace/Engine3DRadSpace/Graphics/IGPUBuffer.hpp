#pragma once
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IGPUBuffer : public IGPUResource
	{
	protected:
		IGPUBuffer() = default;

		IGPUBuffer(const IGPUBuffer&) = delete;
		IGPUBuffer& operator=(const IGPUBuffer&) = delete;

		IGPUBuffer(IGPUBuffer&&) noexcept = default;
		IGPUBuffer& operator=(IGPUBuffer&&) noexcept = default;
	public:
		virtual size_t ReadData(void **data) = 0;
		virtual void SetData(void *data, size_t buffSize) = 0;
		virtual void EndRead() = 0;

		template<typename T>
		void SetData(std::span<T> data)
		{
			SetData(&data[0], data.size_bytes());
		}

		~IGPUBuffer() override = default;
	};
}