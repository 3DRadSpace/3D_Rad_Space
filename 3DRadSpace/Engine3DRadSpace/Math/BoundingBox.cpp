#include "BoundingBox.hpp"
#include "BoundingSphere.hpp"

using namespace Engine3DRadSpace::Math;

Engine3DRadSpace::Math::BoundingBox::BoundingBox(const Vector3& pos, const Vector3& scale):
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

Engine3DRadSpace::Math::BoundingBox::BoundingBox(const BoundingBox& box, const BoundingSphere& sphere) : BoundingBox(BoundingSphere(sphere,box))
{
}

Engine3DRadSpace::Math::BoundingBox::BoundingBox(const BoundingSphere& sph1, BoundingSphere& sph2) : BoundingBox(BoundingSphere(sph1, sph2))
{
}

Vector3 BoundingBox::Center() const
{
    return Position + (Scale / 2);
}