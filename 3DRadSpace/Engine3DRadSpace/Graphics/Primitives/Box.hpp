#pragma once

#include "../../Math/BoundingBox.hpp"
#include "../../Color.hpp"
#include "../ModelMeshPart.hpp"
#include "../../IDrawable3D.hpp"
#include "../Shaders/BlankShader.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Box : public IDrawable3D
	{
		Math::BoundingBox _box;
		Color _color;
		Math::Matrix _worldMat;

		GraphicsDevice *_device;

		std::unique_ptr<VertexBufferV<VertexPositionColor>> _vertices;
		std::unique_ptr<IndexBuffer> _indices;

		std::shared_ptr<Engine3DRadSpace::Graphics::Shaders::BlankShader> _shader;

		std::array<VertexPositionColor, 8> _createVerts(const Math::BoundingBox &b, const Color &color);
	public:
		Box(GraphicsDevice *device,const Math::BoundingBox &b, Color color);

		Box(Box &) = delete;
		Box(Box &&b) noexcept = default;

		Box &operator=(Box &) = delete;
		Box &operator=(Box &&b) noexcept = default;

		Math::BoundingBox GetBoundingBox();
		void SetBoundingBox(const Math::BoundingBox &b);

		Color GetColor();
		void SetColor(const Engine3DRadSpace::Color &color);

		void SetTransform(const Math::Matrix &m);

		virtual void Draw(Engine3DRadSpace::Math::Matrix &view, Engine3DRadSpace::Math::Matrix &projection, double dt) override;
	};
}