#pragma once
#include "../../IDrawable3D.hpp"
#include "../Shaders/BlankShader.hpp"
#include "../VertexBuffer.hpp"
#include "../IndexBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Sphere : public Engine3DRadSpace::IDrawable3D
	{
		GraphicsDevice *_device;
		std::unique_ptr<VertexBufferV<VertexPositionColor>> _vertices;
		std::unique_ptr<IndexBuffer> _indices;

		std::shared_ptr<Shaders::BlankShader> _shader;
	public:
		Sphere(GraphicsDevice *device, float radius, Color color, unsigned resolution);

		Sphere(Sphere &) = delete;
		Sphere(Sphere &&) noexcept = default;

		Sphere &operator=(Sphere &) = delete;
		Sphere &operator=(Sphere &&) noexcept = default;

		Math::Matrix Transform;

		float GetRadius();

		virtual void Draw(Engine3DRadSpace::Math::Matrix &view, Engine3DRadSpace::Math::Matrix &projection, double dt) override;

	};
}