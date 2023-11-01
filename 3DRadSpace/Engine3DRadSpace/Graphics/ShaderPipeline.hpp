#pragma once
#include "IVertexShader.hpp"
#include "IHullShader.hpp"
#include "IDomainShader.hpp"
#include "IGeometryShader.hpp"
#include "IPixelShader.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class DLLEXPORT ShaderPipeline
	{
	protected:
		GraphicsDevice* _device;
		std::unique_ptr<IVertexShader> _vertex;
		std::unique_ptr<IHullShader> _hull;
		std::unique_ptr<IDomainShader> _domain;
		std::unique_ptr<IGeometryShader> _geometry;
		std::unique_ptr<IPixelShader> _pixel;
	public:
		ShaderPipeline(GraphicsDevice *device, IVertexShader* vertexShader, IPixelShader* fragmentShader, IHullShader* hullShader = nullptr,
			IDomainShader* domainShader = nullptr, IGeometryShader* geometryShader = nullptr);

		ShaderPipeline(ShaderPipeline &p) = delete;
		ShaderPipeline(ShaderPipeline&& p) noexcept = default;

		ShaderPipeline &operator =(ShaderPipeline &p) = delete;
		ShaderPipeline& operator =(ShaderPipeline&& p) noexcept = default;
		
		int SetAll() const;
		int SetBasic() const;
		bool SetVertex() const;
		bool SetHull() const;
		bool SetDomain() const;
		bool SetGeometry() const;
		bool SetFragment() const;

		IShader* GetVertexShader() const;
		IShader* GetHullShader() const;
		IShader* GetDomainShader() const;
		IShader* GetGeometryShader() const;
		IShader* GetPixelShader() const;

		virtual ~ShaderPipeline() = default;
	};
}