#include "Texture2D.hpp"
#ifdef _DX11
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <Windows.h>
#endif // _DX11
#include "Error.hpp"

Engine3DRadSpace::Graphics::Texture2D::Texture2D(GraphicsDevice* device, const char *filename)
{
#ifdef _DX11
	ID3D11Resource *resource = static_cast<ID3D11Resource *>(this->texture.Get());

	wchar_t path[_MAX_PATH]{};
	MultiByteToWideChar(CP_ACP, 0, filename,(int) strlen(filename), path, _MAX_PATH);

	HRESULT r = DirectX::CreateWICTextureFromFile(
		device->device.Get(),
		device->context.Get(),
		path,
		&resource,
		this->resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromFile(
			device->device.Get(),
			device->context.Get(),
			path,
			&resource,
			this->resourceView.GetAddressOf()
			);
	}

	Logging::RaiseFatalErrorIfFailed(r, "Failed to create texture from file!",filename);
#endif
}

Engine3DRadSpace::Graphics::Texture2D::Texture2D(GraphicsDevice *device, std::span<Color> colors, unsigned x, unsigned y)
{
#ifdef _DX11
	D3D11_TEXTURE2D_DESC tDesc{};
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tDesc.Height = y;
	tDesc.Width = x;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	Color **colorsCopy = new Color*[y];

	int k = 0;
	for (unsigned i = 0; i < y; i++)
	{
		colorsCopy[i] = new Color[x];
		for (unsigned j = 0; j < x; j++, k++)
		{
			colorsCopy[j][i] = colors[k];
		}
	}

	D3D11_SUBRESOURCE_DATA textureData{};
	textureData.pSysMem = new Color[x * y];
	textureData.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->device->CreateTexture2D(&tDesc, nullptr, this->texture.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to initialize a 2D texture!");

	D3D11_SHADER_RESOURCE_VIEW_DESC resViewDesc{};
	resViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	resViewDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D10_1_SRV_DIMENSION_TEXTURE2D;

	r = device->device->CreateShaderResourceView(this->texture.Get(), nullptr, this->resourceView.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to create a shader resource view!");
#endif
}

void Engine3DRadSpace::Graphics::Texture2D::SetColors(Color **colors, unsigned x, unsigned y)
{
}
