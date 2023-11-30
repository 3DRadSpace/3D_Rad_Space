#include "Viewport.hpp"
#include "Math/Math.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

Vector3 Viewport::Unproject(const Vector3 &source,const Matrix4x4& projection,const Matrix4x4& view,const Matrix4x4& world)
{
	auto matrix = Matrix4x4::Invert(world *  view * projection);

	Vector3 s(source);

	s.X = (((source.X - ScreenRectangle.X) / ((float)ScreenRectangle.Width) * 2.0f) - 1.0f);
	s.Y = -((((source.Y - ScreenRectangle.Y) / ((float)ScreenRectangle.Height)) * 2.0f) - 1.0f);
	s.Z = (source.Z - this->MinDepth) / (this->MaxDepth - this->MinDepth);
	Vector3 vector = Vector3::Transform(source, matrix);
	float a = (((source.X * matrix.M14) + (source.Y * matrix.M24)) + (source.Z * matrix.M34)) + matrix.M44;
	
	if (!Math::WithinEpsilon(a, 1.0f))
	{
		vector.X = vector.X / a;
		vector.Y = vector.Y / a;
		vector.Z = vector.Z / a;
	}
	return vector;

}