#include "Viewport.hpp"

#ifdef __DIRECTXVER

void Engine3DRadSpace::Viewport::SetViewport(ID3D11DeviceContext* context)
{
	D3D11_VIEWPORT view;
	memset(&view, 0, sizeof(D3D11_VIEWPORT));
	view.TopLeftX = (float)this->TopLeftX;
	view.TopLeftY = (float)this->TopLeftY;
	view.Width = (float)this->Width;
	view.Height = (float)this->Height;
	view.MinDepth = (float)this->MinDepth;
	view.MaxDepth = (float)this->MaxDepth;

	context->RSSetViewports(1, &view);
}

#endif