#pragma once
#include "IShader.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class ShaderPipeline
	{
	protected:
		GraphicsDevice* device;
		IShader* vertex;
		IShader* hull;
		IShader* domain;
		IShader* geometry;
		IShader* pixel;

		void destroy();
	public:
		ShaderPipeline(GraphicsDevice *device, IShader* vertexShader, IShader* fragmentShader, IShader* hullShader = nullptr, IShader* domainShader = nullptr, IShader* geometryShader = nullptr);
		ShaderPipeline(ShaderPipeline& p);

		ShaderPipeline& operator =(ShaderPipeline& p);

		int SetAll();
		int SetBasic();
		bool SetVertex();
		bool SetHull();
		bool SetDomain();
		bool SetGeometry();
		bool SetFragment();

		IShader* GetVertexShader();
		IShader* GetHullShader();
		IShader* GetDomainShader();
		IShader* GetGeometryShader();
		IShader* GetFragmentShader();

		virtual ~ShaderPipeline();
	};
}