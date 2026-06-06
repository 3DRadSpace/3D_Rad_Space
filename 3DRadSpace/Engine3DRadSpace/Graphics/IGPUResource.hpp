#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IGraphicsDevice;
	class E3DRSP_GRAPHICS_EXPORT IGPUResource
	{
	protected:
		IGPUResource() = default;

		IGPUResource(const IGPUResource&) = delete;
		IGPUResource& operator=(const IGPUResource&) = delete;

		IGPUResource(IGPUResource&&) noexcept = default;
		IGPUResource& operator=(IGPUResource&&) noexcept = default;
	public:
		virtual void* GetHandle() const noexcept = 0;
		virtual IGraphicsDevice* GetGraphicsDevice() const noexcept = 0;

		virtual ~IGPUResource() = default;
	};
}