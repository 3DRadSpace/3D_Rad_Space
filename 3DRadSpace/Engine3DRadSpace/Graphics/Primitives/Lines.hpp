#include "../VertexBuffer.hpp"
#include "../../IDrawable3D.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class Lines : public Engine3DRadSpace::IDrawable3D
	{
		std::unique_ptr<VertexBufferV<VertexPositionColor>> _vertices;
		std::unique_ptr<RasterizerState> _lineRasterizer;
		GraphicsDevice *_device;
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _oldRasterizerState;
#endif
	public:
		Lines(GraphicsDevice *device, std::span<VertexPositionColor> points);

		Lines(Lines &) = delete;
		Lines(Lines &&) noexcept = default;

		Lines &operator=(Lines &) = delete;
		Lines &operator=(Lines &&) noexcept = default;

		Engine3DRadSpace::Math::Matrix Transform = Engine3DRadSpace::Math::Matrix();

		virtual void Draw(Engine3DRadSpace::Math::Matrix &view, Engine3DRadSpace::Math::Matrix &projection, double dt) override;
	};
}