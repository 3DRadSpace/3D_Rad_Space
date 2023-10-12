#include "BoundingSphere.hpp"
#include "BoundingBox.hpp"

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
	Radius = std::max({ diff.X, diff.Y, diff.Z });
}

BoundingSphere::BoundingSphere(const BoundingSphere& sph1, const BoundingSphere& sph2):
	Center( sph1.Center + sph2.Center / 2),
	Radius( fabsf((sph1.Center - Center).Length()) + std::max(sph1.Radius, sph2.Radius))
{
}

BoundingSphere::BoundingSphere(const BoundingSphere& sph, const BoundingBox& box):
	Center( sph.Center + box.Center() / 2),
	Radius(fabs((sph.Center - Center).Length()) + std::max({ sph.Radius, box.Scale.X, box.Scale.Y, box.Scale.Y }))
{
}

BoundingSphere::BoundingSphere(const BoundingBox& box1, const BoundingBox& box2):
	Center( box1.Center() + box2.Center() / 2),
	Radius( (box1.Center() - Center).Length() + std::max(
		{ 
			box1.Scale.X, box2.Scale.X,
			box1.Scale.Y, box2.Scale.Y,
			box1.Scale.Z, box2.Scale.Z
		}
	))
{
}
