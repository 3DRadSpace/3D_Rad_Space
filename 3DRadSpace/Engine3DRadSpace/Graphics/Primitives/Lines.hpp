#include "../VertexBuffer.hpp"
#include "../../IDrawable3D.hpp"
#include "../Shaders/BlankShader.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Lines : public IDrawable3D
	{
		std::unique_ptr<VertexBufferV<VertexPositionColor>> _vertices;
		std::unique_ptr<RasterizerState> _lineRasterizer;
		GraphicsDevice *_device;

		std::shared_ptr<Shaders::BlankShader> simpleShader;
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _oldRasterizerState;
#endif
	public:
		Lines(GraphicsDevice *device, std::span<VertexPositionColor> points);

		Lines(Lines &) = delete;
		Lines(Lines &&) noexcept = default;

		Lines &operator=(Lines &) = delete;
		Lines &operator=(Lines &&) noexcept = default;

		Math::Matrix4x4 Transform = Math::Matrix4x4();

		virtual void Draw(Math::Matrix4x4 &view, Math::Matrix4x4 &projection, double dt) override;
	};
}