#pragma once
#include "PickingShader.hpp"
#include "..\..\Graphics\RenderTarget.hpp"
#include "..\..\IDrawable3D.hpp"
#include "..\..\Graphics\Model3D.hpp"
#include "..\..\Content\ShaderManager.hpp"
#include "..\..\Math\Point.hpp"

namespace Engine3DRadSpace::Algorithms::Picking
{
	class DLLEXPORT PickingRenderTargetRender : IDrawable3D
	{
		std::shared_ptr<PickingShader> _shader;
		Engine3DRadSpace::GraphicsDevice* _device;
		std::unique_ptr<Graphics::RenderTarget> _renderTarget;
		std::unique_ptr<Graphics::DepthStencilBuffer> _depthBuffer;

		bool _isDrawing = false;
	public:
		PickingRenderTargetRender(GraphicsDevice* device);

		void Begin()
		{
			if (_isDrawing)
			{
				_device->SetRenderTargetAndDepth(_renderTarget.get(), _depthBuffer.get());
				_device->Clear();
				_isDrawing = false;
			}
			else throw std::exception("Begin() already called.");
		}

		void DrawModel(Graphics::Model3D* model,const Math::Matrix &viewWorldProj, unsigned ID)
		{
			if (!_isDrawing) throw std::exception("Begin() was not called");
			_shader->SetAll();
			_shader->SetData(
				PickingShader::Data{
					.MVP = viewWorldProj,
					.ObjectID = ID
				}
			);

			model->Draw();
		}

		/// <summary>
		/// Restores the default render target.
		/// </summary>
		void End()
		{
			_isDrawing = false;
			_device->SetRenderTargetAndDepth(nullptr, nullptr);
		}

		unsigned Pick(const Math::Point& mouseCoords)
		{
			return 0;
		}
	};
}

