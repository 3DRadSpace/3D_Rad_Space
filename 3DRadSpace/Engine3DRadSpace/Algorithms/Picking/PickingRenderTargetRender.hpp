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
		GraphicsDevice* _device;
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
					.ObjectID = ID+1
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

		std::optional<unsigned> Pick(const Math::Point& mouseCoords)
		{
#ifdef _DX11
			D3D11_MAPPED_SUBRESOURCE mappedSubresource;

			auto renderTarget = static_cast<ID3D11Texture2D*>(_renderTarget->RenderTargetHandle());

			HRESULT r = _device->_context->Map(renderTarget, 0, D3D11_MAP_READ, 0, &mappedSubresource);
			if (FAILED(r)) throw Logging::Exception("Failed to map the ID texture!");

			unsigned ID = *static_cast<int*>(mappedSubresource.pData) + (mouseCoords.Y * _renderTarget->Width()) + mouseCoords.X;

			_device->_context->Unmap(renderTarget, 0);

			if (ID != 0) return ID + 1;
			return std::nullopt;
#endif
		}
	};
}

