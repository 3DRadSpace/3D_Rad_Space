#include "Texture2D.h"

#ifdef __DIRECTXVER
Engine3DRadSpace::Texture2D::Texture2D(Game *g,int width, int height, DXGI_FORMAT format)
{
	this->_device = g->GetDevice();
	this->_context = g->GetDeviceContext();

	D3D11_TEXTURE2D_DESC texturedesc;
	memset(&texturedesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	texturedesc.Format = format;
	texturedesc.ArraySize = 1;
	texturedesc.MipLevels = 0;
	texturedesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	texturedesc.SampleDesc.Count = 1;
	texturedesc.SampleDesc.Quality = 0;
	texturedesc.Width = width;
	texturedesc.Height = height;
	texturedesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	texturedesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT r = this->_device->CreateTexture2D(&texturedesc, nullptr, &this->_texture);
	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create a Texture2D!");
	}

	r = this->_device->CreateShaderResourceView((ID3D11Resource*)this->_texture, nullptr, &this->_shaderresourceview);
	if (FAILED(r))
	{
		throw ResourceCreationException("Failed to create the shader resource view", typeid(ID3D11ShaderResourceView));
	}
}

Engine3DRadSpace::Texture2D::Texture2D(Game* game,const std::wstring &path)
{
	_texture = nullptr;
	_shaderresourceview = nullptr;

	_context = game->GetDeviceContext();
	_device = game->GetDevice();

	HRESULT r = DirectX::CreateWICTextureFromFile(_device, path.c_str(), (ID3D11Resource**)&_texture, &_shaderresourceview);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromFile(_device, path.c_str(), (ID3D11Resource**)&_texture, &_shaderresourceview);
		if (FAILED(r))
		{
			throw ResourceCreationException("Failed to create a texture from file!", typeid(ID3D11Texture2D));
		}
	}
}

Engine3DRadSpace::Texture2D::Texture2D(Game* game, const std::string& path)
{
	_texture = nullptr;
	_shaderresourceview = nullptr;

	_context = game->GetDeviceContext();
	_device = game->GetDevice();

	wchar_t filepath[260]; //Windows has a 260 characters limit on the path

	mbstowcs(filepath, path.c_str(), 260); //goddammit M$ WHY

	HRESULT r = DirectX::CreateWICTextureFromFile(_device, filepath, (ID3D11Resource**)&_texture, &_shaderresourceview);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromFile(_device, filepath, (ID3D11Resource**)&_texture, &_shaderresourceview);
		if (FAILED(r))
		{
			throw ResourceCreationException("Failed to create a texture from file!", typeid(ID3D11Texture2D));
		}
	}
}

ID3D11Texture2D* Engine3DRadSpace::Texture2D::GetTexture2D()
{
	return this->_texture;
}

ID3D11ShaderResourceView* Engine3DRadSpace::Texture2D::GetShaderResourceView()
{
	return this->_shaderresourceview;
}

Engine3DRadSpace::Texture2D::~Texture2D()
{
	if (_texture != nullptr) _texture->Release();
	if (_shaderresourceview != nullptr) this->_shaderresourceview->Release();

	this->_texture = nullptr;
	this->_shaderresourceview = nullptr;
}
#endif