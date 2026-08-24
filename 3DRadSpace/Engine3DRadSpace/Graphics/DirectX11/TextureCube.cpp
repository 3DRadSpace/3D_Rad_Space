#include "TextureCube.hpp"
#include "GraphicsDevice.hpp"
#include "../Logging/Exception.hpp"
#include <DDSTextureLoader.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;

TextureCube::TextureCube(GraphicsDevice *device, const std::filesystem::path &filePath) :
	_device(device)
{
	HRESULT r = DirectX::CreateDDSTextureFromFile(
		_device->_device.Get(),
		filePath.c_str(),
		reinterpret_cast<ID3D11Resource**>(_texture.GetAddressOf()),
		&_resourceView
	);
	if(FAILED(r)) throw Logging::Exception("Failed to load the cube texture from the specified file!");

	_setDebugInfo();
}

TextureCube::TextureCube(GraphicsDevice *device,const std::array<ITexture2D*, 6> &cubeMap) :
	_device(device)
{
	std::array<ID3D11Texture2D*, 6> textures;

	for(size_t i = 0; i < 6; i++)
	{
		textures[i] = static_cast<Texture2D*>(cubeMap[i])->_texture.Get();
	}

	D3D11_TEXTURE2D_DESC desc;
	textures[0]->GetDesc(&desc);
	desc.ArraySize = 6;
	desc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;

	UINT mipCount = desc.MipLevels;

	HRESULT r = _device->_device->CreateTexture2D(
		&desc,
		nullptr,
		_texture.ReleaseAndGetAddressOf()
	);
	if(FAILED(r)) throw Logging::Exception("Failed to create the cube texture!");

	for(UINT face = 0; face < 6; ++face)
	{
		for(UINT mip = 0; mip < mipCount; ++mip)
		{
			UINT dstSubresource = D3D11CalcSubresource(mip, face, mipCount);
			UINT srcSubresource = D3D11CalcSubresource(mip, 0, mipCount);
			_device->_context->CopySubresourceRegion(
				_texture.Get(),
				dstSubresource,
				0,
				0,
				0,
				textures[face],
				srcSubresource,
				nullptr
			);
		}
	}

	_createSRV();
	_setDebugInfo();
}

TextureCube::TextureCube(GraphicsDevice* device, D3D11_TEXTURE2D_DESC* desc, Microsoft::WRL::ComPtr<ID3D11Texture2D> &&texture) :
	_device(device),
	_texture(std::move(texture)),
	_size(desc->Width, desc->Height)
{
}

void TextureCube::_createSRV()
{
	HRESULT r = _device->_device->CreateShaderResourceView(
		_texture.Get(),
		nullptr,
		_resourceView.ReleaseAndGetAddressOf()
	);
	if(FAILED(r)) throw Logging::Exception("Failed to create shader resource view for the cube texture!");
}

void TextureCube::_setDebugInfo()
{
#ifdef _DEBUG
	const char textureName[] = "ITextureCube::_texture";
	_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);
	const char srvName[] = "ITextureCube::_resourceView";
	_resourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(srvName) - 1, srvName);
#endif
}

unsigned TextureCube::Width() const noexcept
{
	return _size.X;
}

unsigned TextureCube::Height() const noexcept
{
	return _size.Y;
}

Math::UPoint TextureCube::Size() const noexcept
{
	return _size;
}

void* TextureCube::GetViewHandle() const noexcept
{
	return static_cast<void*>(_resourceView.Get());
}

std::unique_ptr<ITextureCube> TextureCube::CreateStaging()
{
	D3D11_TEXTURE2D_DESC desc{};
	_texture->GetDesc(&desc);

	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	desc.BindFlags = 0;
	desc.MipLevels = 0;
	desc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
	HRESULT r = _device->_device->CreateTexture2D(&desc, nullptr, &stagingTexture);
	if(FAILED(r)) throw Logging::Exception("Failed to create a staging texture!" + std::system_category().message(r));

	_device->_context->CopyResource(stagingTexture.Get(), _texture.Get());

	auto texture = TextureCube(_device, &desc, std::move(stagingTexture));
	return std::make_unique<TextureCube>(std::move(texture));
}

size_t TextureCube::ReadData(size_t subResource, void** data)
{
	if(data == nullptr)
	{
		return 0;
	}

	D3D11_MAPPED_SUBRESOURCE res;
	HRESULT r = _device->_context->Map(_texture.Get(), subResource, D3D11_MAP_READ, 0, &res);
	if(FAILED(r))
	{
		*data = nullptr;
		return 0;
	}

	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);

	auto mipLevel = subResource % desc.MipLevels;
	auto mipHeight = std::max(1u, _size.Y >> mipLevel);

	*data = res.pData;
	return res.RowPitch * mipHeight;
}

void TextureCube::SetData(size_t subResource, void* data, size_t buffSize)
{
	if(!data || buffSize == 0)
		return;

	D3D11_MAPPED_SUBRESOURCE res;
	HRESULT r = _device->_context->Map(_texture.Get(), subResource, D3D11_MAP_WRITE, 0, &res);
	if(FAILED(r)) return;

	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);

	const UINT mipLevel = subResource % desc.MipLevels;
	const UINT mipHeight = std::max(1u, desc.Height >> mipLevel);

	const size_t srcRowSize = buffSize / mipHeight;

	const uint8_t* src = static_cast<const uint8_t*>(data);
	uint8_t* dst = static_cast<uint8_t*>(res.pData);

	for(UINT y = 0; y < mipHeight; ++y)
	{
		memcpy(dst + y * res.RowPitch,
			   src + y * srcRowSize,
			   srcRowSize);
	}

	_device->_context->Unmap(_texture.Get(), subResource);
}

void TextureCube::EndRead(size_t subResource)
{
	_device->_context->Unmap(_texture.Get(), subResource);
}

void* TextureCube::GetHandle() const noexcept
{
	return _texture.Get();
}

IGraphicsDevice* TextureCube::GetGraphicsDevice() const noexcept
{
	return _device;
}