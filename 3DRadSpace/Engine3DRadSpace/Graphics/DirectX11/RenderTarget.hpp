#pragma once
#include "Texture2D.hpp"
#include "../IRenderTarget.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class E3DRSP_GRAPHICS_DX11_EXPORT RenderTarget : public Texture2D, public IRenderTarget
	{
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTarget;

		/// <summary>
		/// Used by GraphicsDevice when creating the backbuffer and swap chain.
		/// </summary>
		/// <param name="device">Graphics device being created</param>
		/// <param name="backbuffer">Backbuffer</param>
		explicit RenderTarget(
			GraphicsDevice* device,
			Microsoft::WRL::ComPtr<ID3D11Texture2D> &&backbuffer,
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &&srv,
			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> &&rtv
		);
	protected:
		explicit RenderTarget(GraphicsDevice* device, std::monostate cpy);
	public:
		/// <summary>
		/// Create a render target with the same size as the backbuffer, and the specified format.
		/// </summary>
		/// <param name="device">Graphics context</param>
		/// <param name="format">Texture color format</param>
		RenderTarget(GraphicsDevice *device, PixelFormat format = PixelFormat::R16G16B16A16_Float);
		/// <summary>
		/// Create a render target with specified size and format.
		/// </summary>
		/// <param name="device">Graphics device</param>
		/// <param name="x">Texture width.</param>
		/// <param name="y">Texture height.</param>
		/// <param name="format">Color format.</param>
		RenderTarget(GraphicsDevice* device, size_t x, size_t y, PixelFormat format = PixelFormat::R16G16B16A16_Float);

		RenderTarget(const RenderTarget&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;

		RenderTarget(RenderTarget&&) noexcept = default;
		RenderTarget& operator=(RenderTarget&&) noexcept = default;

		void* RenderTargetHandle() const noexcept override;

		~RenderTarget() = default;

		friend class GraphicsDevice;
		friend class GraphicsCommandList;
	};
}

