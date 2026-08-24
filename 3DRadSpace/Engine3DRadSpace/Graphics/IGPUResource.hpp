#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IGraphicsDevice;
	/// <summary>
	/// Polymorphic base for classes that manage GPU resources like states.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT IGPUResource
	{
	protected:
		IGPUResource() = default;

		IGPUResource(const IGPUResource&) = delete;
		IGPUResource& operator=(const IGPUResource&) = delete;

		IGPUResource(IGPUResource&&) noexcept = default;
		IGPUResource& operator=(IGPUResource&&) noexcept = default;
	public:
		/// <summary>
		///	Gets an opaque handle to the underlying GPU resource.
		/// </summary>
		/// <returns></returns>
		virtual void* GetHandle() const noexcept = 0;
		/// <summary>
		///	Gets the GraphicsDevice that created this resource.
		/// </summary>
		/// <returns></returns>
		virtual IGraphicsDevice* GetGraphicsDevice() const noexcept = 0;

		virtual ~IGPUResource() = default;
	};
}