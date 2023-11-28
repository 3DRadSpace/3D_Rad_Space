#include "BoundingSphere.hpp"
#include "BoundingBox.hpp"
#include "Ray.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

BoundingSphere::BoundingSphere() : Center(), Radius(0) 
{
}

BoundingSphere::BoundingSphere(Vector3 center, float radius) :
	Center(center),
	Radius(radius)
{
}

BoundingSphere::BoundingSphere(const BoundingBox& box) :
	Center(box.Center())
{
	Vector3 diff = box.Position - box.Center();
	Radius = fabs(std::max({ diff.X, diff.Y, diff.Z }));
}

BoundingSphere::BoundingSphere(const BoundingSphere& sph1, const BoundingSphere& sph2):
	Center( sph1.Center + sph2.Center / 2),
	Radius( fabs(fabsf((sph1.Center - Center).Length()) + std::max(sph1.Radius, sph2.Radius)))
{
}

BoundingSphere::BoundingSphere(const BoundingSphere& sph, const BoundingBox& box):
	Center( sph.Center + box.Center() / 2),
	Radius( fabs(fabs((sph.Center - Center).Length()) + std::max({ sph.Radius, box.Scale.X, box.Scale.Y, box.Scale.Y })))
{
}

BoundingSphere::BoundingSphere(const BoundingBox& box1, const BoundingBox& box2):
	Center( box1.Center() + box2.Center() / 2),
	Radius( fabs((box1.Center() - Center).Length() + std::max(
		{ 
			box1.Scale.X, box2.Scale.X,
			box1.Scale.Y, box2.Scale.Y,
			box1.Scale.Z, box2.Scale.Z
		}
	)))
{
}

bool Engine3DRadSpace::Math::BoundingSphere::Intersects(const BoundingBox& box) const
{
	return box.Intersects(*this);
}

bool Engine3DRadSpace::Math::BoundingSphere::Intersects(const BoundingSphere& sphere) const
{
	return (sphere.Center - Center).LengthSquared() <= pow(sphere.Radius + Radius, 2);
}

bool Engine3DRadSpace::Math::BoundingSphere::Intersects(const Plane& plane) const
{
	//https://www.cuemath.com/geometry/distance-between-point-and-plane/
	float ax = plane.Normal.X * Center.X;
	float by = plane.Normal.Y * Center.Y;
	float cz = plane.Normal.Z * Center.Z;

	float distance = fabs(ax + by + cz + plane.D);
	return distance <= Radius;
}

bool Engine3DRadSpace::Math::BoundingSphere::Intersects(const Ray& ray) const
{
	return ray.Intersects(*this).has_value();
}

bool Engine3DRadSpace::Math::BoundingSphere::Contains(const Vector3& p) const
{
	return (Center - p).LengthSquared() <= Radius * Radius;
}
