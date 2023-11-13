#include "BoundingBox.hpp"
#include "BoundingSphere.hpp"
#include "Math.hpp"
#include "Ray.hpp"

using namespace Engine3DRadSpace::Math;

BoundingBox::BoundingBox(const Vector3& pos, const Vector3& scale):
    Position(pos),
    Scale(scale)
{
}

BoundingBox::BoundingBox(const BoundingSphere& sphere):
    Position( sphere.Center - (Vector3::One() * sphere.Radius)),
    Scale( sphere.Radius, sphere.Radius, sphere.Radius)
{
}

BoundingBox::BoundingBox(const BoundingBox& box1, const BoundingBox& box2)
{
    Vector3 minVec = Vector3(
        std::min(box1.Position.X, box2.Position.X),
        std::min(box1.Position.Y, box2.Position.Y),
        std::min(box1.Position.Z, box2.Position.Z)
    );
    Vector3 maxVec = Vector3(
        std::max(box1.Position.X, box2.Position.X),
        std::max(box1.Position.Y, box2.Position.Y),
        std::max(box1.Position.Z, box2.Position.Z)
    );
    Position = minVec;
    Scale = maxVec - minVec;
}

BoundingBox::BoundingBox(const BoundingBox& box, const BoundingSphere& sphere) : BoundingBox(BoundingSphere(sphere,box))
{
}

BoundingBox::BoundingBox(const BoundingSphere& sph1,const BoundingSphere& sph2) : BoundingBox(BoundingSphere(sph1, sph2))
{

}

Vector3 BoundingBox::Min() const
{
    return Position;
}

Vector3 BoundingBox::Max() const
{
    return Position + Scale;
}

bool BoundingBox::Interescts(const BoundingBox& box) const
{
    return  AABB(Position.X, Scale.X, box.Position.X, box.Scale.X) &&
			AABB(Position.Y, Scale.Y, box.Position.Y, box.Scale.Y) &&
			AABB(Position.Z, Scale.Z, box.Position.Z, box.Scale.Z);
}

bool BoundingBox::Intersects(const BoundingSphere& sphere) const
{
    //https://gamedev.stackexchange.com/questions/156870/how-do-i-implement-a-aabb-sphere-collision
}

bool BoundingBox::Intersects(const Plane& plane) const
{
    //https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html

	// Convert AABB to center-extents representation
    Vector3 c = Center();
    Vector3 e = Max() - c; // Compute positive extents

    // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
    float r = e.X * abs(plane.Normal.X) + e.Y * abs(plane.Normal.Y) + e.Z * abs(plane.Normal.Z);

    // Compute distance of box center from plane
    float s = Vector3::Dot(plane.Normal, c) - plane.D;

    // Intersection occurs when distance s falls within [-r,+r] interval
    return abs(s) <= r; 
}

bool BoundingBox::Intersects(const Ray& ray) const
{
    return ray.Intersects(*this).has_value();
}

Vector3 BoundingBox::Center() const
{
    return Position + (Scale / 2);
}