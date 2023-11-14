#pragma once
#include "../../IDrawable3D.hpp"
#include "../Shaders/BlankShader.hpp"
#include "../VertexBuffer.hpp"
#include "../IndexBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class PlaneQuad : IDrawable3D
	{
		GraphicsDevice* _device;
		std::unique_ptr<VertexBufferV<VertexPositionColor>> _vertices;
		std::unique_ptr<IndexBuffer> _indices;

		std::unique_ptr<RasterizerState> _rasterState;
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _oldRasterState;
#endif

		std::shared_ptr<Shaders::BlankShader> _shader;
	public:
		PlaneQuad(GraphicsDevice* device, std::array<Math::Vector3, 4> points, Color planeColor);

		PlaneQuad(PlaneQuad&) = delete;
		PlaneQuad(PlaneQuad&&) noexcept = default;

		PlaneQuad& operator=(PlaneQuad&) = delete;
		PlaneQuad& operator=(PlaneQuad&&) noexcept = default;

		Math::Matrix4x4 Transform;

		void Draw(Math::Matrix4x4& view, Math::Matrix4x4& projection, double dt) override;
		~PlaneQuad() override = default;
	};
}