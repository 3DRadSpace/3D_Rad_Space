#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents an interface for a render target.
	/// </summary>
	/// <remarks>
	/// A IRenderTarget instance in guaranteed to be a Texture2D, because a render target view requires a texture for read/writing.
	/// The interface was separated from the Texture2D/IGPUMultiBuffer inheritance chain to fix a diamond problem issue.
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT IRenderTarget
	{
	protected:
		IRenderTarget() = default;

		IRenderTarget(const IRenderTarget&) = delete;
		IRenderTarget& operator=(const IRenderTarget&) = delete;

		IRenderTarget(IRenderTarget&&) noexcept = default;
		IRenderTarget& operator=(IRenderTarget&&) noexcept = default;
	public:
		/// <summary>
		/// Gets an handle to the render target view.
		/// </summary>
		/// <returns></returns>
		virtual void* RenderTargetHandle() const noexcept = 0;
		virtual ~IRenderTarget() = default;
	};
}