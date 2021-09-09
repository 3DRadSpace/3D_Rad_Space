#include "Ray.h"

RayResult Ray::Intersects(const Triangle& triangle)
{
    const float EPSILON = 0.0000001;
    Vector3 vertex0 = triangle.PointA;
    Vector3 vertex1 = triangle.PointB;
    Vector3 vertex2 = triangle.PointC;
    Vector3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = Direction.Cross(edge2);
    a = edge1.Dot(h);
    if (a > -EPSILON && a < EPSILON)
        return { false, std::numeric_limits<float>::infinity() };    // This ray is parallel to this triangle.
    f = 1.0 / a;
    s = Origin - vertex0;
    u = f * s.Dot(h);
    if (u < 0.0 || u > 1.0)
        return { false, std::numeric_limits<float>::infinity() };
    q = s.Cross(edge1);
    v = f * Direction.Dot(q);
    if (v < 0.0 || u + v > 1.0f)
        return { false, std::numeric_limits<float>::infinity() };
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * edge2.Dot(q);
    if (t > EPSILON) // ray intersection
    {
        return { true,t };
    }
    else // This means that there is a line intersection but not a ray intersection.
        //return false;
        return {false,t};
}
