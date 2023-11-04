#include "Texture2D.hpp"
#ifdef USING_DX11
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <Windows.h>
#include <ScreenGrab.h>
#include <wincodec.h>
#endif // USING_DX11
#include "../Logging/Exception.hpp"
#include "../Logging/ResourceLoadingError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

Texture2D::Texture2D(GraphicsDevice* device, const std::string &filename):
	_device(device),
	_width(0),
	_height(0)
{
#ifdef USING_DX11
	ID3D11Resource **resource = reinterpret_cast<ID3D11Resource **>(_texture.GetAddressOf());

	wchar_t path[_MAX_PATH]{};
	MultiByteToWideChar(CP_ACP, 0, filename.c_str(), (int)filename.length(), path, _MAX_PATH);

	HRESULT r = DirectX::CreateWICTextureFromFile(
		device->_device.Get(),
		device->_context.Get(),
		path,
		resource,
		_resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromFile(
			device->_device.Get(),
			device->_context.Get(),
			path,
			resource,
			_resourceView.GetAddressOf()
			);
		return;
	}

	if(FAILED(r)) throw ResourceLoadingError(Tag<Texture2D>{}, filename, "Failed to create a texture!");

	_retrieveSize();
#endif
}

Texture2D::Texture2D(GraphicsDevice* device, const std::wstring &filename):
	_device(device)
{
#ifdef USING_DX11
	ID3D11Resource** resource = reinterpret_cast<ID3D11Resource**>(_texture.GetAddressOf());

	HRESULT r = DirectX::CreateWICTextureFromFile(
		device->_device.Get(),
		device->_context.Get(),
		filename.c_str(),
		resource,
		_resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromFile(
			device->_device.Get(),
			device->_context.Get(),
			filename.c_str(),
			resource,
			_resourceView.GetAddressOf()
		);
	}

	if(FAILED(r))
	{
		char mbPath[_MAX_PATH]{};
		WideCharToMultiByte(CP_ACP, 0, filename.c_str(), int(filename.length()), mbPath, _MAX_PATH, nullptr, nullptr);
		throw ResourceLoadingError(Tag<Texture2D>{}, mbPath, "Failed to create a texture!");
	}

	_retrieveSize();
#endif
}

Texture2D::Texture2D(GraphicsDevice *device, std::span<Color> colors, unsigned x, unsigned y):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC tDesc{};
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	tDesc.Height = y;
	tDesc.Width = x;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tDesc.ArraySize = 1;
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	tDesc.MipLevels = 1;

	D3D11_SUBRESOURCE_DATA textureData{};
	textureData.pSysMem = &colors[0];
	textureData.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->_device->CreateTexture2D(&tDesc, &textureData, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!");
#endif
	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice* device, void* buffer, unsigned x, unsigned y, PixelFormat format)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC tDesc{};
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tDesc.Format = _getTextureFormat(format);
	tDesc.Height = y;
	tDesc.Width = x;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tDesc.ArraySize = 1;
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	tDesc.MipLevels = 1;

	D3D11_SUBRESOURCE_DATA textureData{};
	textureData.pSysMem = buffer;
	textureData.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->_device->CreateTexture2D(&tDesc, &textureData, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!");
#endif
	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice* device, Color* colors, unsigned x, unsigned y):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = colors;
	data.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->_device->CreateTexture2D(&desc, &data, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!");
#endif
	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice* device,const uint8_t* imageBuffer, size_t size):
	_device(device)
{
#ifdef USING_DX11
	ID3D11Resource** resource = reinterpret_cast<ID3D11Resource**>(_texture.GetAddressOf());

	HRESULT r = DirectX::CreateWICTextureFromMemory(
		device->_device.Get(),
		device->_context.Get(),
		imageBuffer,
		size,
		resource,
		_resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateWICTextureFromMemory(
			device->_device.Get(),
			device->_context.Get(),
			imageBuffer,
			size,
			resource,
			_resourceView.GetAddressOf()
		);
	}
	if (FAILED(r)) throw Exception("Failed to create texture from memory!");

	_retrieveSize();
#endif
}

Texture2D::Texture2D(GraphicsDevice *device, unsigned x, unsigned y, PixelFormat format):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = _getTextureFormat(format);

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!");
#endif
	_debugInfoTX2D();
}

void Texture2D::_debugInfoTX2D()
{
#ifdef _DEBUG
#ifdef USING_DX11
	const char textureName[] = "Texture2D::_texture";
	_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);

	const char resourceViewName[] = "Texture2D::_resourceView";
	_resourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(resourceViewName) - 1, resourceViewName);
#endif
#endif
}

void Texture2D::_debugInfoRT()
{
#ifdef _DEBUG
#ifdef USING_DX11
	const char textureName[] = "RenderTarget(Texture2D)::_texture";
	_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);

	const char resourceViewName[] = "RenderTarget(Texture2D)::_resourceView";
	_resourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(resourceViewName) - 1, resourceViewName);
#endif
#endif
}

void Texture2D::_retrieveSize()
{
	//Retrieve the image size
	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);

	_width = desc.Width;
	_height = desc.Height;
}

DXGI_FORMAT Texture2D::_getTextureFormat(PixelFormat format)
{
	switch (format)
	{
		case PixelFormat::R32G32B32A32_Typeless: return DXGI_FORMAT_R32G32B32A32_TYPELESS;
		case PixelFormat::R32G32B32A32_Float: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case PixelFormat::R32G32B32A32_UnsignedInt: return DXGI_FORMAT_R32G32B32A32_UINT;
		case PixelFormat::R32G32B32A32_SignedInt: return DXGI_FORMAT_R32G32B32A32_SINT;

		case PixelFormat::R32G32B32_Typeless: return DXGI_FORMAT_R32G32B32_TYPELESS;
		case PixelFormat::R32G32B32_Float: return DXGI_FORMAT_R32G32B32_FLOAT;
		case PixelFormat::R32G32B32_UnsignedInt: return DXGI_FORMAT_R32G32B32_UINT;
		case PixelFormat::R32G32B32_SignedInt: return DXGI_FORMAT_R32G32B32_SINT;

		case PixelFormat::R16G16B16A16_Typeless: return DXGI_FORMAT_R16G16B16A16_TYPELESS;
		case PixelFormat::R16G16B16A16_Float: return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case PixelFormat::R16G16B16A16_UnsignedNormalized: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case PixelFormat::R16G16B16A16_UnsignedInt: return DXGI_FORMAT_R16G16B16A16_UINT;
		case PixelFormat::R16G16B16A16_SignedNormalized: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case PixelFormat::R16G16B16A16_SignedInt: return DXGI_FORMAT_R16G16B16A16_SINT;

		case PixelFormat::R32G32_Typeless: return DXGI_FORMAT_R32G32_TYPELESS;
		case PixelFormat::R32G32_Float: return DXGI_FORMAT_R32G32_FLOAT;
		case PixelFormat::R32G32_UnsignedInt: return DXGI_FORMAT_R32G32_UINT;
		case PixelFormat::R32G32_SignedInt: return DXGI_FORMAT_R32G32_SINT;

		case PixelFormat::R32G8X24_Typeless: return DXGI_FORMAT_R32G8X24_TYPELESS;

		case PixelFormat::D32_Float_S8X24_UnsignedInt: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		case PixelFormat::R32_Float_X8X24_Typeless: return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
		case PixelFormat::X32_Typeless_G8X24_UnsignedInt: return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;

		case PixelFormat::R10G10B10A2_Typeless: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case PixelFormat::R10G10B10A2_UnsignedNormalized: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case PixelFormat::R10G10B10A2_UnsignedInt: return DXGI_FORMAT_R10G10B10A2_UINT;
		case PixelFormat::R11G11B10_Float: return DXGI_FORMAT_R11G11B10_FLOAT;

		case PixelFormat::R8G8B8A8_Typeless: return DXGI_FORMAT_R8G8B8A8_TYPELESS;
		case PixelFormat::R8G8B8A8_UnsignedNormalized: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case PixelFormat::R8G8B8A8_UnsignedNormalized_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case PixelFormat::R8G8B8A8_UnsignedInt: return DXGI_FORMAT_R8G8B8A8_UINT;
		case PixelFormat::R8G8B8A8_SignedNormalized: return DXGI_FORMAT_R8G8B8A8_SNORM;
		case PixelFormat::R8G8B8A8_SignedInt: return DXGI_FORMAT_R8G8B8A8_SINT;
			
		case PixelFormat::R16G16_Typeless: return DXGI_FORMAT_R16G16_TYPELESS;
		case PixelFormat::R16G16_Float: return DXGI_FORMAT_R16G16_FLOAT;
		case PixelFormat::R16G16_UnsignedNormalized: return DXGI_FORMAT_R16G16_UNORM;
		case PixelFormat::R16G16_UnsignedInt: return DXGI_FORMAT_R16G16_UINT;
		case PixelFormat::R16G16_SignedNormalized: return DXGI_FORMAT_R16G16_SNORM;
		case PixelFormat::R16G16_SignedInt: return DXGI_FORMAT_R16G16_SINT;

		case PixelFormat::R32_Typeless: return DXGI_FORMAT_R32_TYPELESS;
		case PixelFormat::D32_Float: return DXGI_FORMAT_D32_FLOAT;
		case PixelFormat::R32_Float: return DXGI_FORMAT_R32_FLOAT;
		case PixelFormat::R32_UnsignedInt: return DXGI_FORMAT_R32_UINT;
		case PixelFormat::R32_SignedInt: return DXGI_FORMAT_R32_SINT;
		
		case PixelFormat::R24G8_Typeless: return DXGI_FORMAT_R24G8_TYPELESS;
		case PixelFormat::D24_UnsignedNormalized_S8_UnsignedInt: return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case PixelFormat::R24_UnsignedNormalized_X8_Typeless: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case PixelFormat::X24_Typeless_G8_UnsignedInt: return DXGI_FORMAT_X24_TYPELESS_G8_UINT;

		case PixelFormat::R8G8_Typeless: return DXGI_FORMAT_R8G8_TYPELESS;
		case PixelFormat::R8G8_UnsignedNormalized: return DXGI_FORMAT_R8G8_UNORM;
		case PixelFormat::R8G8_UnsignedInt: return DXGI_FORMAT_R8G8_UINT;
		case PixelFormat::R8G8_SignedNormalized: return DXGI_FORMAT_R8G8_SNORM;
		case PixelFormat::R8G8_SignedInt: return DXGI_FORMAT_R8G8_SINT;
			
		case PixelFormat::R16_Typeless: return DXGI_FORMAT_R16_TYPELESS;
		case PixelFormat::R16_Float: return DXGI_FORMAT_R16_FLOAT;
		case PixelFormat::D16_UnsignedNormalized: return DXGI_FORMAT_D16_UNORM;
		case PixelFormat::R16_UnsignedNormalized: return DXGI_FORMAT_R16_UNORM;
		case PixelFormat::R16_UnsignedInt: return DXGI_FORMAT_R16_UINT;
		case PixelFormat::R16_SignedNormalized: return DXGI_FORMAT_R16_SNORM;
		case PixelFormat::R16_SignedInt: return DXGI_FORMAT_R16_SINT;
			
		case PixelFormat::R8_Typeless: return DXGI_FORMAT_R8_TYPELESS;
		case PixelFormat::R8_UnsignedNormalized: return DXGI_FORMAT_R8_UNORM;
		case PixelFormat::R8_UnsignedInt: return DXGI_FORMAT_R8_UINT;
		case PixelFormat::R8_SignedNormalized: return DXGI_FORMAT_R8_SNORM;
		case PixelFormat::R8_SignedInt: return DXGI_FORMAT_R8_SINT;
		case PixelFormat::A8_UnsignedNormalized: return DXGI_FORMAT_A8_UNORM;

		case PixelFormat::R1_UnsignedNormalized: return DXGI_FORMAT_R1_UNORM;
		case PixelFormat::R9G9B9E5_SHAREDEXP: return  DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
		case PixelFormat::R8G8_B8G8_UnsignedNormalized: return DXGI_FORMAT_R8G8_B8G8_UNORM;
		case PixelFormat::G8R8_G8B8_UnsignedNormalized: return DXGI_FORMAT_G8R8_G8B8_UNORM;
			
		case PixelFormat::BC1_Typeless: return DXGI_FORMAT_BC1_TYPELESS;
		case PixelFormat::BC1_UnsignedNormalized: return DXGI_FORMAT_BC1_UNORM;
		case PixelFormat::BC1_UnsignedNormalized_SRGB: return DXGI_FORMAT_BC1_UNORM_SRGB;
			
		case PixelFormat::BC2_Typeless: return DXGI_FORMAT_BC2_TYPELESS;
		case PixelFormat::BC2_UnsignedNormalized: return DXGI_FORMAT_BC2_UNORM;
		case PixelFormat::BC2_UnsignedNormalized_SRGB: return DXGI_FORMAT_BC2_UNORM_SRGB;

		case PixelFormat::BC3_Typeless: return DXGI_FORMAT_BC3_TYPELESS;
		case PixelFormat::BC3_UnsignedNormalized: return DXGI_FORMAT_BC3_UNORM;
		case PixelFormat::BC3_UnsignedNormalized_SRGB: return DXGI_FORMAT_BC3_UNORM_SRGB;
			
		case PixelFormat::BC4_Typeless: return DXGI_FORMAT_BC4_TYPELESS;
		case PixelFormat::BC4_UnsignedNormalized: return DXGI_FORMAT_BC4_UNORM;
		case PixelFormat::BC4_SignedNormalized: return DXGI_FORMAT_BC4_SNORM;

		case PixelFormat::BC5_Typeless: return DXGI_FORMAT_BC5_TYPELESS;
		case PixelFormat::BC5_UnsignedNormalized: return DXGI_FORMAT_BC5_UNORM;
		case PixelFormat::BC5_SignedNormalized: return DXGI_FORMAT_BC5_SNORM;

		case PixelFormat::B5G6R5_UnsignedNormalized: return DXGI_FORMAT_B5G6R5_UNORM;
		case PixelFormat::B5G5R5A1_UnsignedNormalized: return DXGI_FORMAT_B5G5R5A1_UNORM;

		case PixelFormat::B8G8R8A8_UnsignedNormalized: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case PixelFormat::B8G8R8X8_UnsignedNormalized: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case PixelFormat::R10G10B10_XR_BIAS_A2_UnsignedNormalized: return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;

		case PixelFormat::B8G8R8A8_Typeless: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case PixelFormat::B8G8R8A8_UnsignedNormalized_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case PixelFormat::B8G8R8X8_Typeless: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case PixelFormat::B8G8R8X8_UnsignedNormalized_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
			
		case PixelFormat::BC6H_Typeless: return DXGI_FORMAT_BC6H_TYPELESS;
		case PixelFormat::BC6H_UF16: return DXGI_FORMAT_BC6H_UF16;
		case PixelFormat::BC6H_SF16: return DXGI_FORMAT_BC6H_SF16;

		case PixelFormat::BC7_Typeless: return DXGI_FORMAT_BC7_TYPELESS;
		case PixelFormat::BC7_UnsignedNormalized: return DXGI_FORMAT_BC7_UNORM;
		case PixelFormat::BC7_UnsignedNormalized_SRGB: return DXGI_FORMAT_BC7_UNORM_SRGB;
		case PixelFormat::AYUV: return DXGI_FORMAT_AYUV;
			
		case PixelFormat::Y410: return DXGI_FORMAT_Y410;
		case PixelFormat::Y416: return DXGI_FORMAT_Y416;
		case PixelFormat::NV12: return DXGI_FORMAT_NV12;
		case PixelFormat::P010: return DXGI_FORMAT_P010;
		case PixelFormat::P016: return DXGI_FORMAT_P016;
		case PixelFormat::Video_YUV_420_Opaque: return DXGI_FORMAT_420_OPAQUE;
		
		case PixelFormat::YUY2: return DXGI_FORMAT_YUY2;
		case PixelFormat::Y210: return DXGI_FORMAT_Y210;
		case PixelFormat::Y216: return DXGI_FORMAT_Y216;
		case PixelFormat::NV11: return DXGI_FORMAT_NV11;
		case PixelFormat::AI44: return DXGI_FORMAT_AI44;
		case PixelFormat::IA44: return DXGI_FORMAT_IA44;
		case PixelFormat::P8: return DXGI_FORMAT_P8;
		case PixelFormat::A8P8: return DXGI_FORMAT_A8P8;
		case PixelFormat::B4G4R4A4_UnsignedNormalized: return DXGI_FORMAT_B4G4R4A4_UNORM;

		case PixelFormat::P208: return DXGI_FORMAT_P208;
		case PixelFormat::V208: return DXGI_FORMAT_V208;
		case PixelFormat::V408: return DXGI_FORMAT_V408;
	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}

Texture2D::Texture2D(GraphicsDevice *device, unsigned x, unsigned y, bool bindRenderTarget, PixelFormat format):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (bindRenderTarget ? D3D11_BIND_RENDER_TARGET : 0);
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!");
#endif
	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice *device, bool bindRenderTarget, PixelFormat format):
	_device(device)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = device->_resolution.X;
	desc.Height = device->_resolution.Y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (bindRenderTarget ? D3D11_BIND_RENDER_TARGET : 0);
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!");
#endif

	_width = device->_resolution.X;
	_height = device->_resolution.Y;
	_debugInfoRT();
}

Texture2D::Texture2D(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Texture2D>&& texture, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>&& resource) :
	_device(device),
	_texture(std::move(texture)),
	_resourceView(std::move(resource))
{
	_retrieveSize();
}

Texture2D::Texture2D(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Texture2D>&& texture) :
	_device(device),
	_texture(std::move(texture)),
	_resourceView(nullptr)
{
	_retrieveSize();
}

void Texture2D::SetColors(Color** colors, unsigned x, unsigned y)
{
#ifdef USING_DX11
	D3D11_MAPPED_SUBRESOURCE resource;

	HRESULT r = _device->_context->Map(_texture.Get(), 0, D3D11_MAP_WRITE, 0, &resource);
	if (FAILED(r)) throw std::exception("Failed to map a texture!");

	memcpy(resource.pData, colors, sizeof(Color) * x * y);
	_device->_context->Unmap(_texture.Get(), 0);
#endif
}

Texture2D Texture2D::CreateStaging(Texture2D* texture)
{
#ifdef USING_DX11
	D3D11_TEXTURE2D_DESC desc{};
	texture->_texture->GetDesc(&desc);

	//Keep a copy of the original texture desc.
	D3D11_TEXTURE2D_DESC resizedTextureDesc = desc;

	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.BindFlags = 0;
	desc.MipLevels = 0;
	desc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
	HRESULT r = texture->_device->_device->CreateTexture2D(&desc, nullptr, &stagingTexture);
	if (FAILED(r)) throw Exception("Failed to create a staging texture!");
#endif

	return Texture2D(texture->_device, std::move(stagingTexture));
}

void Texture2D::Resize(unsigned newX, unsigned newY)
{
#ifdef USING_DX11
	//1.) Create a staging texture.
	D3D11_TEXTURE2D_DESC desc{};
	_texture->GetDesc(&desc);

	//Keep a copy of the original texture desc.
	D3D11_TEXTURE2D_DESC resizedTextureDesc = desc;
	resizedTextureDesc.Width = newX; //Set the new sizes
	resizedTextureDesc.Height = newY;

	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.BindFlags = 0;
	desc.MipLevels = 0;
	desc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, &stagingTexture);
	if (FAILED(r)) throw Exception("Failed to create a staging texture!");

	//2.) Copy initial texture into the staging texture
	_device->_context->CopyResource(stagingTexture.Get(), _texture.Get());

	D3D11_MAPPED_SUBRESOURCE mappedRes{};
	r = _device->_context->Map(stagingTexture.Get(), 0, D3D11_MAP_READ, 0, &mappedRes);
	if (FAILED(r)) throw Exception("Failed to map the staging texture!");

	struct ColorInt
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

	std::span<ColorInt> oldTexture(reinterpret_cast<ColorInt *>(mappedRes.pData), _width * _height);

	//3.) Create a new image buffer with the new size
	std::unique_ptr<ColorInt[]> newTextureData = std::make_unique<ColorInt[]>(newX * newY);
	std::span<ColorInt> nData(newTextureData.get(), newX * newY);

	//4.) Use nearest neighbor interpolation for resampling
	float ratioX = static_cast<float>(_width) / newX;
	float ratioY = static_cast<float>(_height) / newY;

	for(unsigned j = 0; j < newY; j++)
	{
		for(unsigned i = 0; i < newX; i++)
		{
			unsigned x = unsigned(i * ratioX);
			unsigned y = unsigned(j * ratioY);

			nData[i + (j * newX)] = oldTexture[x + (y * _width)];
		}
	}
	_device->_context->Unmap(stagingTexture.Get(), 0);

	//5.) Finally, replace the old texture with the new resized one
	D3D11_SUBRESOURCE_DATA newSubresource{};
	newSubresource.pSysMem = newTextureData.get();
	newSubresource.SysMemPitch = sizeof(ColorInt) * newX;

	resizedTextureDesc.MipLevels = 1;
	r = _device->_device->CreateTexture2D(&resizedTextureDesc, &newSubresource, _texture.ReleaseAndGetAddressOf());
	if (FAILED(r)) throw Exception("Failed to recreate the texture!");
	
	r = _device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.ReleaseAndGetAddressOf()); //recreate the shader resource view for the new texture
	if (FAILED(r)) throw Exception("Failed to recreate the shader resource view!");
#endif
	//6.) Update fields
	_width = newX;
	_height = newY;
}

void Texture2D::SaveToFile(const std::string &path)
{
#ifdef USING_DX11
	wchar_t wpath[_MAX_PATH]{};
	MultiByteToWideChar(CP_ACP, 0, path.c_str(), -1, wpath, _MAX_PATH);

	HRESULT r = DirectX::SaveWICTextureToFile(_device->_context.Get(), _texture.Get(), GUID_ContainerFormatPng, wpath, nullptr, nullptr, true);
	if(FAILED(r)) throw Exception("Failed to save file!");
#endif
}

unsigned Texture2D::Width()
{
	return _width;
}

unsigned Texture2D::Height()
{
	return _height;
}

Texture2D Texture2D::Clone()
{
	Texture2D staging = CreateStaging(this);

#ifdef USING_DX11
	Microsoft::WRL::ComPtr<ID3D11Texture2D> copy = nullptr;

	D3D11_TEXTURE2D_DESC desc{};
	this->_texture->GetDesc(&desc);

	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, copy.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create staging texture");

	_device->_context->CopyResource(copy.Get(), staging._texture.Get());

	return Texture2D(_device, std::move(copy));
#endif
}

void* Texture2D::TextureHandle() const
{
	return _texture.Get();
}

void* Texture2D::ResourceViewHandle() const
{
	return _resourceView.Get();
}

