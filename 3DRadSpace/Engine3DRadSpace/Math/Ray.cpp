#include "Ray.hpp"

//https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
std::optional<float> Engine3DRadSpace::Math::Ray::Intersects(const Sphere &sph)
{
    float a = Direction.Dot(Origin - sph.Center);
    float nabla = powf(a, 2) - ((Origin - sph.Center).LengthSquared() - powf(sph.Radius, 2));
    
    float epsilon = 1e-6f;

    if(nabla < 0) return std::nullopt;
    else return a - sqrtf(nabla);

}

//https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
std::optional<float> Engine3DRadSpace::Math::Ray::Intersects(const Triangle &tri)
{
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    Vector3 vertex0 = tri.PointA;
    Vector3 vertex1 = tri.PointB;
    Vector3 vertex2 = tri.PointC;
    Vector3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = Vector3::Cross(Direction, edge2);
    a = edge1.Dot(h);

    if(a > -epsilon && a < epsilon)
        return false;    // This ray is parallel to this triangle.

    f = 1.0 / a;
    s = Origin - vertex0;
    u = f * s.Dot(h);

    if(u < 0.0 || u > 1.0)
        return false;

    q = Vector3::Cross(s, edge1);
    v = f * Direction.Dot(q);

    if(v < 0.0 || u + v > 1.0)
        return false;

    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * edge2.Dot(q);

    if(t > epsilon) // ray intersection
        return t;
    else // This means that there is a line intersection but not a ray intersection.
        return std::nullopt;
}
