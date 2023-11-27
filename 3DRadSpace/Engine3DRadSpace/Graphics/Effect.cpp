#include "Effect.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

Effect::Effect(GraphicsDevice *device, IVertexShader *vertexShader, IPixelShader *fragmentShader, IHullShader *hullShader,
	IDomainShader *domainShader, IGeometryShader *geometryShader ):
	_device(device),
	_vertex(vertexShader),
	_hull(hullShader),
	_domain(domainShader),
	_geometry(geometryShader),
	_pixel(fragmentShader)
{
}

int Effect::SetAll() const
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetHull()) ++r;
	if(SetDomain()) ++r;
	if(SetGeometry()) ++r;
	if(SetFragment()) ++r;
	return r;
}

int Effect::SetBasic() const
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetFragment()) ++r;
	return r;
}

bool Effect::SetVertex() const
{
	if(_vertex == nullptr) return false;

	_device->SetShader(_vertex.get());
	return true;
}

bool Effect::SetHull() const
{
	if(_hull == nullptr) return false;

	_device->SetShader(_hull.get());
	return true;
}

bool Effect::SetDomain() const
{
	if(_domain == nullptr) return false;

	_device->SetShader(_domain.get());
	return true;
}

bool Effect::SetGeometry() const
{
	if(_geometry == nullptr) return false;

	_device->SetShader(_geometry.get());
	return true;
}

bool Effect::SetFragment() const
{
	if(_pixel == nullptr) return false;

	_device->SetShader(_pixel.get());
	return true;
}

IShader* Effect::GetVertexShader() const
{
	return _vertex.get();
}

IShader* Effect::GetHullShader() const 
{
	return _hull.get();
}

IShader* Effect::GetDomainShader() const
{
	return _domain.get();
}

IShader* Effect::GetGeometryShader() const
{
	return _geometry.get();
}

IShader* Effect::GetPixelShader() const
{
	return _pixel.get();
}