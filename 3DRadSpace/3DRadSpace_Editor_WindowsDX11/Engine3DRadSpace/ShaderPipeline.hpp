#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{

	class ShaderPipeline
	{
	protected:
		GraphicsDevice* _device;
		IShader* _vertex;
		IShader* _hull;
		IShader* _domain;
		IShader* _geometry;
		IShader* _pixel;
	public:
		ShaderPipeline(GraphicsDevice *device, IShader* vertexShader, IShader* fragmentShader, IShader* hullShader = nullptr, IShader* domainShader = nullptr, IShader* geometryShader = nullptr);
	
		int SetAll();
		int SetBasic();
		bool SetVertex();
		bool SetHull();
		bool SetDomain();
		bool SetGeometry();
		bool SetFragment();

		virtual ~ShaderPipeline();
	};
}