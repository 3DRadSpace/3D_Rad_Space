#include "SphericalBillboard.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

SphericalBillboard::SphericalBillboard(IGraphicsDevice* device) : CilindricalBillboard(device)
{
}

Matrix4x4 SphericalBillboard::billboardMatrix() const noexcept
{
	Vector3 x_axis(View.M11, View.M21, View.M31);
	Vector3 y_axis(View.M12, View.M22, View.M32);
	Vector3 z_axis(View.M13, View.M23, View.M33);

	Vector3 cam_pos = -(x_axis * View.M41 + y_axis * View.M42 + z_axis * View.M43);

	auto model = Matrix4x4::CreateSphericalBillboard(Position, cam_pos, y_axis, z_axis);
	return model * View * Projection;
}