#include "Plane.hpp"
#include "BoundingBox.hpp"
#include "BoundingSphere.hpp"
#include "Ray.hpp"

using namespace Engine3DRadSpace::Math;

bool Plane::Intersects(const BoundingBox& box) const
{
    return box.Intersects(*this);
}

bool Plane::Intersects(const BoundingSphere& sphere) const
{
    return sphere.Intersects(*this);
}

bool Plane::Intersects(const Ray& ray) const
{
    return ray.Intersects(*this).has_value();
}

bool Engine3DRadSpace::Math::Plane::Contains(const Vector3& p) const
{
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    //The point is contained inside the plane, if the coordinates satisfy the plane equation N_x * x + N_y * y + N_z * z == D
    float p_eval = Normal.X * p.X + Normal.Y * p.Y + Normal.Z * p.Z;

    return (D - epsilon) <= p_eval && p_eval <= (D + epsilon);
}
