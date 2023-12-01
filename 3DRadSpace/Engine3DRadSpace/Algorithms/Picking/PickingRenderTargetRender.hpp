#pragma once
#include "PickingShader.hpp"
#include "..\..\Graphics\RenderTarget.hpp"
#include "..\..\IDrawable3D.hpp"
#include "..\..\Graphics\Model3D.hpp"
#include "..\..\Content\ShaderManager.hpp"
#include "..\..\Math\Point.hpp"
#include "../../Graphics/Rendering/IRenderer.hpp"

namespace Engine3DRadSpace::Algorithms::Picking
{
	class DLLEXPORT PickingRenderTargetRender : Graphics::Rendering::IRenderer
	{
		std::shared_ptr<PickingShader> _shader;
		std::unique_ptr<Graphics::RenderTarget> _renderTarget;
		std::unique_ptr<Graphics::DepthStencilBuffer> _depthBuffer;

		bool _isDrawing = false;
	public:
		PickingRenderTargetRender(GraphicsDevice* device);

		void Begin() override;

		/// <summary>
		/// Restores the default render target.
		/// </summary>
		void End() override;

		std::optional<unsigned> Pick(const Math::Point& mouseCoords);
	};
}

