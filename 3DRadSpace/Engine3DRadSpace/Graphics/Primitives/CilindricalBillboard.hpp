#pragma once
#include "IPrimitive.hpp"
#include "../../Core/IDrawable3D.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT CilindricalBillboard : public IPrimitive
	{
	protected:
		Math::Matrix4x4 _mvp() const noexcept override;
	public:
		CilindricalBillboard(IGraphicsDevice* device);

		/// <summary>
		/// Camera view matrix.
		/// </summary>
		Math::Matrix4x4 View;
		/// <summary>
		/// Camera projection matrix.
		/// </summary>
		Math::Matrix4x4 Projection;
	
		Math::Vector3 Position;
		Math::Vector2 Scale = Math::Vector2::One();
		Math::Vector3 Axis = Math::Vector3::UnitY();
	
		ITexture2D* Texture;

		static std::array<VertexPositionUV, 4> CreateVertices();

		void Draw3D() override;

		~CilindricalBillboard() override = default;
	};
}