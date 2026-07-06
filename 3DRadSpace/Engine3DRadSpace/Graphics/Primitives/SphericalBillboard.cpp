#include "SphericalBillboard.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

SphericalBillboard::SphericalBillboard(IGraphicsDevice* device) : CylindricalBillboard(device)
{
}

Matrix4x4 SphericalBillboard::_mvp() const noexcept
{
	auto v = View;
	auto v_inv = v;
	v_inv.Invert();

	Vector3 cam_pos(v_inv.M41, v_inv.M42, v_inv.M43);
	Vector3 x_axis(v.M11, v.M21, v.M31);
	Vector3 y_axis(v.M12, v.M22, v.M32);
	Vector3 z_axis(v.M13, v.M23, v.M33);

	Vector3 fwd = cam_pos + z_axis;
	Vector3 up = cam_pos + y_axis;

	// Use Position field if set, otherwise extract from Transform
	Vector3 objectPos = (Position != Vector3::Zero()) ? Position : Vector3(Transform.M41, Transform.M42, Transform.M43);
	auto model = Matrix4x4::CreateSphericalBillboard(objectPos, cam_pos, up, fwd);
	auto scale = Matrix4x4::CreateScale(Vector3(Scale.X, Scale.Y, 1.0f));
	return scale * model * View * Projection;
}