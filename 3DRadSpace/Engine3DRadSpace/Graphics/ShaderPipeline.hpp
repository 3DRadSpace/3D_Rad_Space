#pragma once
#include "IVertexShader.hpp"
#include "IHullShader.hpp"
#include "IDomainShader.hpp"
#include "IGeometryShader.hpp"
#include "IPixelShader.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class ShaderPipeline
	{
	protected:
		GraphicsDevice* device;
		IVertexShader* vertex;
		IHullShader* hull;
		IDomainShader* domain;
		IGeometryShader* geometry;
		IPixelShader* pixel;

		void destroy();
	public:
		ShaderPipeline(GraphicsDevice *device, IVertexShader* vertexShader, IPixelShader* fragmentShader, IHullShader* hullShader = nullptr,
			IDomainShader* domainShader = nullptr, IGeometryShader* geometryShader = nullptr);
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