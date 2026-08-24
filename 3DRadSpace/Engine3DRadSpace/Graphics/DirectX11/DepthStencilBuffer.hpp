#pragma once
#include "../IDepthStencilBuffer.hpp"
#include "GraphicsDevice.hpp"
#include "Texture2D.hpp"
#include "DirectX11.h"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	/// <summary>
	/// Represents the depth stencil buffer.
	/// </summary>
	/// <remarks>
	/// Since this is a large resource, usually the same size as the backbuffer, copy constructors are removed.
	/// </remarks>
	class E3DRSP_GRAPHICS_DX11_EXPORT DepthStencilBuffer : public IDepthStencilBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthView;

		D3D11_TEXTURE2D_DESC _defaultDepthDesc(size_t x, size_t y);
		D3D11_DEPTH_STENCIL_VIEW_DESC _defaultDepthViewDesc();
		D3D11_SHADER_RESOURCE_VIEW_DESC _defaultShaderViewDesc();

		std::unique_ptr<Texture2D> _depthTexture;
		GraphicsDevice *_device;
		void _createDepthTexture(size_t x, size_t y);

		DepthStencilBuffer(
			GraphicsDevice* device,
			Microsoft::WRL::ComPtr<ID3D11DepthStencilView>&& depthView,
			Microsoft::WRL::ComPtr<ID3D11Texture2D>&& depthTexture,
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>&& depthShaderView
		);
	public:
		/// <summary>
		/// Creates a depth stencil buffer.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		explicit DepthStencilBuffer(GraphicsDevice* device);

		/// <summary>
		/// Creates a depth stencil buffer with specified sizes.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		/// <param name="x">Width.</param>
		/// <param name="y">Height.</param>
		explicit DepthStencilBuffer(GraphicsDevice* device, size_t x, size_t y);

		DepthStencilBuffer(DepthStencilBuffer &) = delete;
		DepthStencilBuffer(DepthStencilBuffer &&buff) noexcept = default;

		DepthStencilBuffer &operator=(DepthStencilBuffer &) = delete;
		DepthStencilBuffer &operator=(DepthStencilBuffer &&buff) noexcept = default;

		/// <summary>
		/// Gets the depth texture native handle.
		/// </summary>
		/// <returns>ID3D11Texture2D in DX11.</returns>
		void* GetDepthTextureHandle() const noexcept;
		
		/// <summary>
		/// Gets the depth stencil texture.
		/// </summary>
		/// <returns>Depth Stencil texture pointer.</returns>
		ITexture2D* GetDepthTexture() const noexcept override;

		std::unique_ptr<ITexture2D> CloneDepthTexture() override;

		/// <summary>
		/// Gets the native depth stencil view handle.
		/// </summary>
		/// <returns>ID3D11DepthStencilView</returns>
		void* GetHandle() const noexcept override;
		virtual IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~DepthStencilBuffer() override = default;

		friend class GraphicsDevice;
		friend class GraphicsCommandList;
	};
}
