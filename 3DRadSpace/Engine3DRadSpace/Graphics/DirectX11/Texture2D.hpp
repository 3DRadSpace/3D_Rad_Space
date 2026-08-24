#pragma once
#include "../PixelFormat.hpp"
#include "../../Math/Size.hpp"
#include "../../Content/IAsset.hpp"
#include "../../Math/Color.hpp"
#include "../ITexture2D.hpp"
#include "../BufferUsage.hpp"
#include "DirectX11.h"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class DepthStencilBuffer;
	class GraphicsDevice;
	class TextureCube;
	/// <summary>
	/// Represents a 2D texture.
	/// <remarks>
	/// </remarks>
	class E3DRSP_GRAPHICS_DX11_EXPORT Texture2D : public ITexture2D
	{
		size_t _width;
		size_t _height;

		void _debugInfoTX2D();
		void _debugInfoRT();

	protected:
		explicit Texture2D(GraphicsDevice* device, std::monostate dummy, Microsoft::WRL::ComPtr<ID3D11Texture2D>&& texture);

		Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _resourceView;
		GraphicsDevice *_device;
		PixelFormat _format;

		void _retrieveSize();

		/// <summary>
		/// Used by RenderTarget.
		/// </summary>
		/// <param name="device"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="bindRenderTarget">Set to true.</param>
		/// <param name="format"></param>
		explicit Texture2D(
			GraphicsDevice *device,
			size_t x,
			size_t y,
			bool bindRenderTarget,
			PixelFormat format = PixelFormat::R32G32B32A32_Float
		);
		/// <summary>
		/// Used by RenderTarget.
		/// </summary>
		/// <param name="device"></param>
		/// <param name="dummy">Hack. Used because C++ converts const char* to bool by default over std::filesystem::path.</param>
		/// <param name="bindRenderTarget">Bind render target creation flag</param>
		/// <param name="format">Texture format.</param>
		explicit Texture2D(GraphicsDevice *device, std::monostate dummy, bool bindRenderTarget, PixelFormat format = PixelFormat::R32G32B32A32_Float);

		/// <summary>
		/// Used by RenderTarget to create a null texture.
		/// </summary>
		Texture2D(GraphicsDevice* device);
	public:
		/// <summary>
		/// Loads a texture from a file.
		/// </summary>
		/// <param name="device">Device context</param>
		/// <param name="path">Image file</param>
		Texture2D(GraphicsDevice* device, const std::filesystem::path& path);

		/// <summary>
		/// Constructs an Texture2D instance directly from D3D11 texture and shader resource view.
		/// </summary>
		/// <param name="device">Device context</param>
		/// <param name="texture">D3D11 texture</param>
		/// <param name="resource">D3D11 shader resource view</param>
		explicit Texture2D(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Texture2D>&& texture, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>&& resource);

		/// <summary>
		/// Creates a texture from a span of Colors.
		/// </summary>
		/// <param name="device">Device context.</param>
		/// <param name="colors">Color array. Size must be x * y.</param>
		/// <param name="x">Width of the texture</param>
		/// <param name="y">Height</param>
		explicit Texture2D(GraphicsDevice *device, std::span<Math::Color> colors, size_t x, size_t y);
		/// <summary>
		/// Creates a texture from a buffer with a specified pixel format.
		/// </summary>
		/// <param name="device">Device context.</param>
		/// <param name="colors">Color array. Size must be x * y. If usage is "ReadOnlyGPU_WriteOnlyCPU"(Dynamic), this can be null.</param>
		/// <pram name="x">Width of the texture.</param>
		/// <param name="y">Height of the texture.</param>
		/// <param name="format">Pixel format.</param>
		explicit Texture2D(
			GraphicsDevice *device,
			void* buffer,
			size_t x,
			size_t y,
			PixelFormat format = PixelFormat::R32G32B32A32_Float,
			BufferUsage usage = BufferUsage::ReadOnlyGPU_WriteOnlyCPU
		);
		/// <summary>
		/// Creates a texture from an image buffer.
		/// </summary>
		/// <param name="device">Device context.</param>
		/// <param name="imageBuffer">Must be an image.</param>
		/// <param name="size">Size of the buffer.</param>
		/// <remarks>
		/// This calls CreateWICTextureFromMemory.
		/// </remarks>
		explicit Texture2D(GraphicsDevice *device, const uint8_t* imageBuffer, size_t size);

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D&&) noexcept = default;

		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&&) noexcept = default;

		void SetColors(Math::Color** colors, unsigned x, unsigned y);

		void SaveToFile(const std::filesystem::path& path) override;

		unsigned Width() const noexcept override;
		unsigned Height() const noexcept override;
		Math::Point Size() const noexcept override;

		virtual void* GetHandle() const noexcept override;
		virtual IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		size_t ReadData(size_t subResource, void **data) override;
		void SetData(size_t subResource, void *data, size_t buffSize) override;
		void EndRead(size_t subResource) override;

		[[nodiscard]] virtual std::unique_ptr<ITexture2D> CreateStaging();
		Texture2D Clone();

		void* GetViewHandle() const noexcept;

		PixelFormat Format() const noexcept;

		virtual ~Texture2D() = default;

		friend class GraphicsDevice;
		friend class GraphicsCommandList;

		friend class VertexShader;
		friend class FragmentShader;
		friend class HullShader;
		friend class DomainShader;
		friend class GeometryShader;
		friend class DepthStencilBuffer;

		friend class TextureCube;
	};
}

