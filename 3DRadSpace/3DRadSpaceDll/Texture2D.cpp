#include "Texture2D.h"

#ifdef __DIRECTXVER
Texture2D::Texture2D(Game *g,int width, int height, DXGI_FORMAT format)
{
	this->_device = g->GetDevice();
	_device->GetImmediateContext(&this->_context);
	_device->AddRef();
	_context->AddRef();
	
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
}

Texture2D::Texture2D(const std::string &path)
{
	_texture = nullptr;
	_context = nullptr;
	_device = nullptr;
}

Texture2D::~Texture2D()
{
	if (_texture != nullptr) _texture->Release();
}

template<class T>
inline T* Texture2D::GetData(size_t &size_out)
{
	
}

template<class T>
inline void Texture2D::SetData(T* data, size_t size)
{
}
#endif