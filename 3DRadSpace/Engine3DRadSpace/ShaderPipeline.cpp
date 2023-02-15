#include "ShaderPipeline.hpp"

Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::ShaderPipeline(GraphicsDevice* device, IShader* vertexShader, IShader* fragmentShader, IShader* hullShader, IShader* domainShader, IShader* geometryShader):
	_device(device),
	_vertex(vertexShader),
	_hull(hullShader),
	_domain(domainShader),
	_geometry(geometryShader),
	_pixel(fragmentShader)
{
}

int Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetAll()
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetHull()) ++r;
	if(SetDomain()) ++r;
	if(SetGeometry()) ++r;
	if(SetFragment()) ++r;
	return r;
}

int Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetBasic()
{
	int r = 0;
	if(SetVertex()) ++r;
	if(SetFragment()) ++r;
	return r;
}

bool Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetVertex()
{
	if(_vertex == nullptr) return false;

	_device->SetShader(_vertex);
	return true;
}

bool Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetHull()
{
	if(_hull == nullptr) return false;

	_device->SetShader(_hull);
	return true;
}

bool Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetDomain()
{
	if(_domain == nullptr) return false;

	_device->SetShader(_domain);
	return true;
}

bool Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetGeometry()
{
	if(_geometry == nullptr) return false;

	_device->SetShader(_geometry);
	return true;
}

bool Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetFragment()
{
	if(_pixel == nullptr) return false;

	_device->SetShader(_pixel);
	return true;
}

Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::~ShaderPipeline()
{
	if(this->_vertex != nullptr)
	{
		delete this->_vertex;
		this->_vertex = nullptr;
	}
	if(this->_hull != nullptr)
	{
		delete this->_hull;
		this->_hull = nullptr;
	}
	if(this->_domain != nullptr)
	{
		delete this->_domain;
		this->_domain = nullptr;
	}
	if(this->_geometry != nullptr)
	{
		delete this->_geometry;
		this->_geometry = nullptr;
	}
	if(this->_pixel != nullptr)
	{
		delete this->_pixel;
		this->_pixel = nullptr;
	}
}
