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

Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::ShaderPipeline(ShaderPipeline& p) : 
	_device(p._device),
	_vertex(p._vertex),
	_hull(p._hull),
	_domain(p._domain),
	_geometry(p._geometry),
	_pixel(p._pixel)
{
	this->_destroy();
}

Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::ShaderPipeline(ShaderPipeline &&p) noexcept:
	_device(p._device),
	_vertex(p._vertex),
	_hull(p._hull),
	_domain(p._domain),
	_geometry(p._geometry),
	_pixel(p._pixel)
{
	p._vertex = nullptr;
	p._domain = nullptr;
	p._geometry = nullptr;
	p._hull = nullptr;
	p._pixel = nullptr;
	p._vertex = nullptr;
	p._geometry = nullptr;
}

ShaderPipeline& Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::operator=(ShaderPipeline& p)
{
	_destroy();
	_device = p._device;
	_vertex = p._vertex;
	_hull = p._hull;
	_domain = p._domain;
	_geometry = p._geometry;
	_pixel = p._pixel;
	return *this;
}

int ShaderPipeline::SetAll()
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetHull()) ++r;
	if(SetDomain()) ++r;
	if(SetGeometry()) ++r;
	if(SetFragment()) ++r;
	return r;
}

int ShaderPipeline::SetBasic()
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetFragment()) ++r;
	return r;
}

bool ShaderPipeline::SetVertex()
{
	if(_vertex == nullptr) return false;

	_device->SetShader(_vertex);
	return true;
}

bool ShaderPipeline::SetHull()
{
	if(_hull == nullptr) return false;

	_device->SetShader(_hull);
	return true;
}

bool ShaderPipeline::SetDomain()
{
	if(_domain == nullptr) return false;

	_device->SetShader(_domain);
	return true;
}

bool ShaderPipeline::SetGeometry()
{
	if(_geometry == nullptr) return false;

	_device->SetShader(_geometry);
	return true;
}

bool ShaderPipeline::SetFragment()
{
	if(_pixel == nullptr) return false;

	_device->SetShader(_pixel);
	return true;
}

IShader* ShaderPipeline::GetVertexShader()
{
	return _vertex;
}

IShader* ShaderPipeline::GetHullShader()
{
	return _hull;
}

IShader* ShaderPipeline::GetDomainShader()
{
	return _domain;
}

IShader* ShaderPipeline::GetGeometryShader()
{
	return _geometry;
}

IShader* ShaderPipeline::GetPixelShader()
{
	return _pixel;
}

ShaderPipeline::~ShaderPipeline()
{
	_destroy();
}

void ShaderPipeline::_destroy()
{
	if (_vertex != nullptr)
	{
		delete _vertex;
		_vertex = nullptr;
	}
	if (_hull != nullptr)
	{
		delete _hull;
		_hull = nullptr;
	}
	if (_domain != nullptr)
	{
		delete _domain;
		_domain = nullptr;
	}
	if (_geometry != nullptr)
	{
		delete _geometry;
		_geometry = nullptr;
	}
	if (_pixel != nullptr)
	{
		delete _pixel;
		_pixel = nullptr;
	}
}