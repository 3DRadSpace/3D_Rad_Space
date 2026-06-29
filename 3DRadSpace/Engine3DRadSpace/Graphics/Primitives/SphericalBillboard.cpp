#include "SphericalBillboard.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

SphericalBillboard::SphericalBillboard(IGraphicsDevice* device) : CilindricalBillboard(device)
{
}

Matrix4x4 SphericalBillboard::_mvp() const noexcept
{
	Vector3 cam_pos(-View.M41, -View.M42, -View.M43);
	Vector3 x_axis(View.M11, View.M21, View.M31);
	Vector3 y_axis(View.M11, View.M21, View.M31);
	Vector3 z_axis(View.M11, View.M21, View.M31);

	Vector3 fwd = cam_pos + z_axis;
	Vector3 up = cam_pos + y_axis;
	Vector3 right = cam_pos + x_axis;

	auto model = Matrix4x4::CreateSphericalBillboard(Position, cam_pos, up, fwd);
	return model * View * Projection;
}