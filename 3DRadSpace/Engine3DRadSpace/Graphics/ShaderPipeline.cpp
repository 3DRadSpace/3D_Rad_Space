#include "ShaderPipeline.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

ShaderPipeline::ShaderPipeline(GraphicsDevice *device, IVertexShader *vertexShader, IPixelShader *fragmentShader, IHullShader *hullShader,
	IDomainShader *domainShader, IGeometryShader *geometryShader ):
	_device(device),
	_vertex(vertexShader),
	_hull(hullShader),
	_domain(domainShader),
	_geometry(geometryShader),
	_pixel(fragmentShader)
{
}

int ShaderPipeline::SetAll() const
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetHull()) ++r;
	if(SetDomain()) ++r;
	if(SetGeometry()) ++r;
	if(SetFragment()) ++r;
	return r;
}

int ShaderPipeline::SetBasic() const
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetFragment()) ++r;
	return r;
}

bool ShaderPipeline::SetVertex() const
{
	if(_vertex == nullptr) return false;

	_device->SetShader(_vertex.get());
	return true;
}

bool ShaderPipeline::SetHull() const
{
	if(_hull == nullptr) return false;

	_device->SetShader(_hull.get());
	return true;
}

bool ShaderPipeline::SetDomain() const
{
	if(_domain == nullptr) return false;

	_device->SetShader(_domain.get());
	return true;
}

bool ShaderPipeline::SetGeometry() const
{
	if(_geometry == nullptr) return false;

	_device->SetShader(_geometry.get());
	return true;
}

bool ShaderPipeline::SetFragment() const
{
	if(_pixel == nullptr) return false;

	_device->SetShader(_pixel.get());
	return true;
}

IShader* ShaderPipeline::GetVertexShader() const
{
	return _vertex.get();
}

IShader* ShaderPipeline::GetHullShader() const 
{
	return _hull.get();
}

IShader* ShaderPipeline::GetDomainShader() const
{
	return _domain.get();
}

IShader* ShaderPipeline::GetGeometryShader() const
{
	return _geometry.get();
}

IShader* ShaderPipeline::GetPixelShader() const
{
	return _pixel.get();
}