#include "RenderTarget.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

RenderTarget::RenderTarget(GraphicsDevice *device, PixelFormat format) :
	Texture2D(device, nullptr, 0, 0, format)
{
	(void)device;
	(void)format;
}

RenderTarget::RenderTarget(GraphicsDevice * device, size_t x, size_t y, PixelFormat format) 
	: Texture2D(device, nullptr, x, y, format)
{
	(void)device;
	(void)x;
	(void)y;
	(void)format;
}

void* RenderTarget::RenderTargetHandle() const noexcept
{
	return nullptr;
}