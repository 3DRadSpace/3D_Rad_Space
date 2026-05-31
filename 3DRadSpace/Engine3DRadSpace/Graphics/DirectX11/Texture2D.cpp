#include "Texture2D.hpp"

#include <directxtk/WICTextureLoader.h>
#include <directxtk/DDSTextureLoader.h>
#include <Windows.h>
#include <directxtk/ScreenGrab.h>
#include <wincodec.h>

#pragma comment( lib, "dxguid.lib") 
#include "../Logging/Exception.hpp"
#include "../Logging/AssetLoadingError.hpp"
#include "GraphicsDevice.hpp"
#include "RenderTarget.hpp"
#include "SamplerState.hpp"
#include "../IGraphicsCommandList.hpp"
#include "BufferUsage.hpp"
#include "PixelFormat.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

Texture2D::Texture2D(GraphicsDevice* device) :
	_device(device),
	_width(0),
	_height(0),
	_format(PixelFormat::Unknown)
{
}

Texture2D::Texture2D(GraphicsDevice* device, const std::filesystem::path &path):
	_device(device)
{
	auto filename = path.wstring();
	ID3D11Resource** resource = reinterpret_cast<ID3D11Resource**>(_texture.GetAddressOf());

	HRESULT r = DirectX::CreateWICTextureFromFileEx(
		device->_device.Get(),
		device->_context.Get(),
		filename.c_str(),
		0u,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		0,
		DirectX::DX11::WIC_LOADER_FORCE_SRGB,
		resource,
		_resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromFileEx(
			device->_device.Get(),
			device->_context.Get(),
			filename.c_str(),
			0,
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_SHADER_RESOURCE,
			0,
			0,
			DirectX::DX11::DDS_LOADER_FLAGS::DDS_LOADER_FORCE_SRGB,
			resource,
			_resourceView.GetAddressOf()
		);
	}

	if(FAILED(r))
	{
		char mbPath[_MAX_PATH]{};
		WideCharToMultiByte(CP_ACP, 0, filename.c_str(), int(filename.length()), mbPath, _MAX_PATH, nullptr, nullptr);
		throw AssetLoadingError(Tag<Texture2D>{}, mbPath, std::system_category().message(r));
	}

	_retrieveSize();
}

Texture2D::Texture2D(GraphicsDevice *device, std::span<Color> colors, size_t x, size_t y):
	_device(device),
	_width(x),
	_height(y)
{
	D3D11_TEXTURE2D_DESC tDesc{};
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
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
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view! " + std::system_category().message(r));

	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice* device, void* buffer, size_t x, size_t y, PixelFormat format, BufferUsage usage):
	_device(device),
	_width(x),
	_height(y)
{
	D3D11_TEXTURE2D_DESC tDesc{};
	
	tDesc.CPUAccessFlags = BufferUsage_ToDX11CPUFlag(usage);
	tDesc.Format = PixelFormat_ToDX11(format);
	tDesc.Height = y;
	tDesc.Width = x;
	tDesc.Usage = BufferUsage_ToDirectX11(usage);
	tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tDesc.ArraySize = 1;
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	tDesc.MipLevels = 1;

	D3D11_SUBRESOURCE_DATA textureData{};
	textureData.pSysMem = buffer;
	textureData.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->_device->CreateTexture2D(&tDesc, buffer != nullptr ? &textureData : nullptr, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!" + std::system_category().message(r));

	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice* device,const uint8_t* imageBuffer, size_t size):
	_device(device)
{
	auto resource = reinterpret_cast<ID3D11Resource**>(_texture.GetAddressOf());

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
	if (FAILED(r)) throw Exception("Failed to create texture from memory!" + std::system_category().message(r));

	_retrieveSize();
}

void Texture2D::_debugInfoTX2D()
{
#ifdef _DEBUG
	const char textureName[] = "Texture2D::_texture";
	_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);

	const char resourceViewName[] = "Texture2D::_resourceView";
	_resourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(resourceViewName) - 1, resourceViewName);
#endif
}

void Texture2D::_debugInfoRT()
{
#ifdef _DEBUG
	const char textureName[] = "RenderTarget(Texture2D)::_texture";
	_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);

	const char resourceViewName[] = "RenderTarget(Texture2D)::_resourceView";
	_resourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(resourceViewName) - 1, resourceViewName);
#endif
}

void Texture2D::_retrieveSize()
{
	//Retrieve the image size
	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);

	_width = desc.Width;
	_height = desc.Height;
	_format = PixelFormat_FromDX11(desc.Format);
}

Texture2D::Texture2D(GraphicsDevice *device, size_t x, size_t y, bool bindRenderTarget, PixelFormat format):
	_device(device),
	_width(x),
	_height(y)
{
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (bindRenderTarget ? D3D11_BIND_RENDER_TARGET : 0);
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = PixelFormat_ToDX11(format);

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!" + std::system_category().message(r));

	_debugInfoTX2D();
}

Texture2D::Texture2D(GraphicsDevice *device, std::monostate dummy, bool bindRenderTarget, PixelFormat format):
	_device(device)
{
	(void)dummy;

	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = device->_resolution.X;
	desc.Height = device->_resolution.Y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (bindRenderTarget ? D3D11_BIND_RENDER_TARGET : 0);
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = PixelFormat_ToDX11(format);

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to initialize a 2D texture!" + std::system_category().message(r));

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a shader resource view!" + std::system_category().message(r));

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

Texture2D::Texture2D(GraphicsDevice* device, std::monostate dummy, Microsoft::WRL::ComPtr<ID3D11Texture2D> && texture) :
	_device(device),
	_texture(std::move(texture)),
	_resourceView(nullptr)
{
	(void)dummy;
	_retrieveSize();
}

void Texture2D::SetColors(Color** colors, unsigned x, unsigned y)
{
	D3D11_MAPPED_SUBRESOURCE resource;

	HRESULT r = _device->_context->Map(_texture.Get(), 0, D3D11_MAP_WRITE, 0, &resource);
	if (FAILED(r)) throw Exception("Failed to map a texture!" + std::system_category().message(r));

	memcpy_s(resource.pData, resource.DepthPitch, colors, sizeof(Color) * x * y);
	_device->_context->Unmap(_texture.Get(), 0);
}

std::unique_ptr<ITexture2D> Texture2D::CreateStaging()
{
	D3D11_TEXTURE2D_DESC desc{};
	_texture->GetDesc(&desc);

	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, &stagingTexture);
	if(FAILED(r)) throw Exception("Failed to create a staging texture!" + std::system_category().message(r));

	_device->_context->CopyResource(stagingTexture.Get(), _texture.Get());

	return std::make_unique<Texture2D>(std::move(Texture2D(_device, std::monostate(), std::move(stagingTexture))));
}

void Texture2D::SaveToFile(const std::filesystem::path& path)
{
	HRESULT r = DirectX::SaveWICTextureToFile(_device->_context.Get(), _texture.Get(), GUID_ContainerFormatPng, path.wstring().c_str(), nullptr, nullptr, true);
	if(FAILED(r)) throw Exception("Failed to save file!" + std::system_category().message(r));
}

unsigned Texture2D::Width() const noexcept
{
	return _width;
}

unsigned Texture2D::Height() const noexcept
{
	return _height;
}

Point Texture2D::Size() const noexcept
{
	return Point(static_cast<int>(_width), static_cast<int>(_height));
}

Texture2D Texture2D::Clone()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> copy = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv = nullptr;

	D3D11_TEXTURE2D_DESC desc{};
	this->_texture->GetDesc(&desc);

	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, copy.GetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create staging texture" + std::system_category().message(r));

	_device->_context->CopyResource(copy.Get(), _texture.Get());

	r = _device->_device->CreateShaderResourceView(_texture.Get(), nullptr, srv.GetAddressOf()); //recreate the shader resource view for the new texture
	if (FAILED(r)) throw Exception("Failed to recreate the shader resource view!" + std::system_category().message(r));

	return Texture2D(_device, std::move(copy), std::move(srv));
}

PixelFormat Texture2D::Format() const noexcept
{
	return _format;
}

void Texture2D::EndRead(size_t resourceID)
{
	_device->_context->Unmap(_texture.Get(), resourceID);
}

void* Texture2D::GetHandle() const noexcept
{
	return _resourceView.Get();
}

IGraphicsDevice* Texture2D::GetGraphicsDevice() const noexcept
{
	return _device;
}

size_t Texture2D::ReadData(size_t subResource, void **data)
{
	assert(data != nullptr);
	if(data == nullptr) return 0;

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	HRESULT r = _device->_context->Map(_texture.Get(), subResource, D3D11_MAP_READ, 0, &mappedResource);
	if(SUCCEEDED(r))
	{
		*data = mappedResource.pData;
		return mappedResource.RowPitch * _height;
	}
	else
	{
		*data = nullptr;
		return 0;
	}
}

void Texture2D::SetData(size_t subResource, void *data, size_t buffSize)
{
	D3D11_MAPPED_SUBRESOURCE resource;

	HRESULT r = _device->_context->Map(_texture.Get(), 0, D3D11_MAP_WRITE, 0, &resource);
	if(FAILED(r)) throw Exception("Failed to map a texture!" + std::system_category().message(r));

	memcpy_s(resource.pData, buffSize, data, buffSize);
	_device->_context->Unmap(_texture.Get(), 0);
}

void* Texture2D::GetViewHandle() const noexcept
{
	return _resourceView.Get();
}