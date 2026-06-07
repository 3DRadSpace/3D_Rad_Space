#pragma once
#include "../ModelMeshPart.hpp"
#include "RenderPassType.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class RenderingManager;

	/// <summary>
	/// Represents a rendering pipeline that allows multiple rendering effects.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT IRenderer
	{
	protected:
		IGraphicsDevice* _device;
		RenderingManager* _owner;

		IRenderer(IGraphicsDevice* device, RenderingManager* owner);

		IRenderer(const IRenderer&) = delete;
		IRenderer& operator=(const IRenderer&) = delete;

		IRenderer(IRenderer&&) noexcept = default;
		IRenderer& operator=(IRenderer&&) noexcept = default;
	public:
		RenderingManager* GetOwner() const noexcept;
		IGraphicsDevice* GetGraphicsDevice() const noexcept;

		/// <summary>
		/// Gets the render pass type this renderer handles. Default is Opaque.
		/// Override this to specify which batched meshes this renderer should draw.
		/// </summary>
		virtual RenderPassType GetRenderPassType() const noexcept;

		/// <summary>
		/// Prepares the graphics pipeline for this effect.
		/// </summary>
		virtual void Begin() = 0;
		/// <summary>
		/// Submits a mesh part to this effect.
		/// </summary>
		/// <param name="part">Mesh</param>
		virtual void Draw(ModelMeshPart* part, Effect* effect = nullptr);
		/// <summary>
		/// Restores the previous states, and depending on the effect, draws all submited meshes. (Unless meshes are not batched).
		/// </summary>
		virtual void End() = 0;

		virtual ~IRenderer() = default;

		friend class RenderingManager;
	};
}