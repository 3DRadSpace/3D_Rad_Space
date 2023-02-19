#include "ShaderPipeline.hpp"

Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::ShaderPipeline(GraphicsDevice* device, IShader* vertexShader, IShader* fragmentShader, IShader* hullShader, IShader* domainShader, IShader* geometryShader):
	device(device),
	vertex(vertexShader),
	hull(hullShader),
	domain(domainShader),
	geometry(geometryShader),
	pixel(fragmentShader)
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
	if(vertex == nullptr) return false;

	device->SetShader(vertex);
	return true;
}

bool Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetHull()
{
	if(hull == nullptr) return false;

	device->SetShader(hull);
	return true;
}

bool Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetDomain()
{
	if(domain == nullptr) return false;

	device->SetShader(domain);
	return true;
}

bool Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetGeometry()
{
	if(geometry == nullptr) return false;

	device->SetShader(geometry);
	return true;
}

bool Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::SetFragment()
{
	if(pixel == nullptr) return false;

	device->SetShader(pixel);
	return true;
}

Engine3DRadSpace::Graphics::Shaders::ShaderPipeline::~ShaderPipeline()
{
	if(this->vertex != nullptr)
	{
		delete this->vertex;
		this->vertex = nullptr;
	}
	if(this->hull != nullptr)
	{
		delete this->hull;
		this->hull = nullptr;
	}
	if(this->domain != nullptr)
	{
		delete this->domain;
		this->domain = nullptr;
	}
	if(this->geometry != nullptr)
	{
		delete this->geometry;
		this->geometry = nullptr;
	}
	if(this->pixel != nullptr)
	{
		delete this->pixel;
		this->pixel = nullptr;
	}
}
