#include "ShaderPipeline.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;

ShaderPipeline::ShaderPipeline(GraphicsDevice* device, IShader* vertexShader, IShader* fragmentShader, IShader* hullShader, IShader* domainShader, IShader* geometryShader):
	device(device),
	vertex(vertexShader),
	hull(hullShader),
	domain(domainShader),
	geometry(geometryShader),
	pixel(fragmentShader)
{
}

Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::ShaderPipeline(ShaderPipeline& p) : 
	device(p.device),
	vertex(p.vertex),
	hull(p.hull),
	domain(p.domain),
	geometry(p.geometry),
	pixel(p.pixel)
{
	this->destroy();
}

ShaderPipeline& Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::operator=(ShaderPipeline& p)
{
	destroy();
	this->device = p.device;
	this->vertex = p.vertex;
	this->hull = p.hull;
	this->domain = p.domain;
	this->geometry = p.geometry;
	this->pixel = p.pixel;
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
	if(vertex == nullptr) return false;

	device->SetShader(vertex);
	return true;
}

bool ShaderPipeline::SetHull()
{
	if(hull == nullptr) return false;

	device->SetShader(hull);
	return true;
}

bool ShaderPipeline::SetDomain()
{
	if(domain == nullptr) return false;

	device->SetShader(domain);
	return true;
}

bool ShaderPipeline::SetGeometry()
{
	if(geometry == nullptr) return false;

	device->SetShader(geometry);
	return true;
}

bool ShaderPipeline::SetFragment()
{
	if(pixel == nullptr) return false;

	device->SetShader(pixel);
	return true;
}

IShader* ShaderPipeline::GetVertexShader()
{
	return this->vertex;
}

IShader* ShaderPipeline::GetHullShader()
{
	return this->hull;
}

IShader* ShaderPipeline::GetDomainShader()
{
	return this->domain;
}

IShader* ShaderPipeline::GetGeometryShader()
{
	return this->geometry;
}

IShader* ShaderPipeline::GetFragmentShader()
{
	return this->pixel;
}

ShaderPipeline::~ShaderPipeline()
{
	destroy();
}

void ShaderPipeline::destroy()
{
	if (this->vertex != nullptr)
	{
		delete this->vertex;
		this->vertex = nullptr;
	}
	if (this->hull != nullptr)
	{
		delete this->hull;
		this->hull = nullptr;
	}
	if (this->domain != nullptr)
	{
		delete this->domain;
		this->domain = nullptr;
	}
	if (this->geometry != nullptr)
	{
		delete this->geometry;
		this->geometry = nullptr;
	}
	if (this->pixel != nullptr)
	{
		delete this->pixel;
		this->pixel = nullptr;
	}
}