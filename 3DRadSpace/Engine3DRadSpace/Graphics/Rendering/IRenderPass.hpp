#pragma once
#include "DrawCall.hpp"

namespace Engine3DRadSpace
{
	class IGame;

	namespace Graphics
	{
		class IGraphicsDevice;

		namespace Rendering
		{
			/// <summary>
			/// Represents a rendering pipeline that allows multiple rendering effects.
			/// </summary>
			class E3DRSP_GRAPHICS_RENDERING_EXPORT IRenderPass
			{
			protected:
				IGraphicsDevice* _device;
				IGame* _owner = nullptr;

				IRenderPass(IGraphicsDevice* device);

				IRenderPass(const IRenderPass&) = delete;
				IRenderPass& operator=(const IRenderPass&) = delete;

				IRenderPass(IRenderPass&&) noexcept = default;
				IRenderPass& operator=(IRenderPass&&) noexcept = default;
			public:
				void SetOwner(IGame* owner) noexcept;
				IGame* GetOwner() const noexcept;

				/// <summary>
				/// Prepares the graphics pipeline for this effect.
				/// </summary>
				virtual void Begin() = 0;
				/// <summary>
				/// Submits a mesh part to this effect. The mesh vertex, index buffers and shaders will be set.
				/// </summary>
				/// <param name="part">Mesh</param>
				virtual void Draw(DrawCall* drawCall);
				/// <summary>
				/// Draws all submited meshes, then restores the previous graphics pipeline if necessary.
				/// </summary>
				virtual void End() = 0;

				IGraphicsDevice* GetDevice() const noexcept;

				virtual ~IRenderPass() = default;
			};
		}
	}
}