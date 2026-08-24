#pragma once
#include "../ITextureCube.hpp"
#include "../ITexture2D.hpp"
#include "DirectX11.h"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class GraphicsDevice;
	class E3DRSP_GRAPHICS_DX11_EXPORT TextureCube : public ITextureCube
	{
		GraphicsDevice *_device;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _resourceView;
		Math::UPoint _size;

		void _createSRV();
		void _setDebugInfo();

		TextureCube(GraphicsDevice* device, D3D11_TEXTURE2D_DESC* desc, Microsoft::WRL::ComPtr<ID3D11Texture2D> &&texture);
	public:
		/// <summary>
		/// Loads a cube texture from a DDS file.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		/// <param name="filePath">DDS file.</param>
		/// <remarks>
		/// If the specified image is not a cube texture, an exception is thrown.
		/// </remarks>
		TextureCube(GraphicsDevice *device, const std::filesystem::path &filePath);
		/// <summary>
		/// Creates a TextureCube from 6 Texture2D objects. All 6 Texture2D objects must have the same dimensions, and the same format.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		/// <param name="cubeMap">DDS file.</param>
		/// <remarks>
		/// The newly created TextureCube will have data copied from cubeMap, so the argument isn't moved, nor destroyed.
		/// </remarks>
		TextureCube(GraphicsDevice *device, const std::array<ITexture2D*, 6> &cubeMap);

		Math::UPoint Size() const noexcept override;
		unsigned Width() const noexcept override;
		unsigned Height() const noexcept override;

		void* GetViewHandle() const noexcept override;
		std::unique_ptr<ITextureCube> CreateStaging() override;

		size_t ReadData(size_t subResource, void** data) override;
		void SetData(size_t subResource, void* data, size_t buffSize) override;
		void EndRead(size_t subResource)  override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		friend class VertexShader;
		friend class FragmentShader;
		friend class HullShader;
		friend class DomainShader;
		friend class GeometryShader;
		friend class DepthStencilBuffer;
	};
}