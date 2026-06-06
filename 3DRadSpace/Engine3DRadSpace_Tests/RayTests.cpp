#include "pch.h"
#include <Engine3DRadSpace\Math\Ray.hpp>
#include <Engine3DRadSpace\Math\Triangle.hpp>
#include <Engine3DRadSpace\Math\BoundingBox.hpp>
#include <Engine3DRadSpace\Math\BoundingPlane.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

TEST(IntersectionTests, Ray_Triangle1)
{
	Ray r(Vector3(0, 0, 0), Vector3(0, 0, 1));

	Triangle tri
	{
		Vector3(-1, -1, 10),
		Vector3(1, -1, 10),
		Vector3(0, 1, 10),
	};

	EXPECT_FLOAT_EQ(r.Intersects(tri), 10.0f);
}

TEST(IntersectionTests, Ray_Triangle2)
{
	//Ray is in opposite direction
	Ray r(Vector3(0, 0, 0), Vector3(0, 0, -1));

	Triangle tri
	{
		Vector3(-1, -1, 10),
		Vector3(1, -1, 10),
		Vector3(0, 1, 10),
	};

	EXPECT_TRUE(std::isnan(r.Intersects(tri)));
}

TEST(IntersectionTests, Ray_Triangle3)
{
	//Ray is parallel to the triangle
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0,0,1)
	);

	Triangle tri
	{
		Vector3(-1,2,-1),
		Vector3(-1,2,1),
		Vector3(0,2,5),
	};

	EXPECT_TRUE(std::isnan(r.Intersects(tri)));
}

TEST(IntersectionTests, Ray_Triangle4)
{
	// Ray misses the triangle (passes through plane but outside triangle bounds)
	Ray r(
		Vector3(5, 5, 0),
		Vector3(0, 0, 1)
	);

	Triangle tri
	{
		Vector3(-1, -1, 10),
		Vector3(1, -1, 10),
		Vector3(0, 1, 10),
	};

	EXPECT_TRUE(std::isnan(r.Intersects(tri)));
}

TEST(IntersectionTests, Ray_Triangle5)
{
	// Ray intersects triangle at an edge
	Ray r(
		Vector3(0, -1, 0),
		Vector3(0, 0, 1)
	);

	Triangle tri
	{
		Vector3(-1, -1, 10),
		Vector3(1, -1, 10),
		Vector3(0, 1, 10),
	};

	EXPECT_FLOAT_EQ(r.Intersects(tri), 10.0f);
}

TEST(IntersectionTests, Ray_Triangle6)
{
	// Ray intersects triangle at a vertex
	Ray r(
		Vector3(-1, -1, 0),
		Vector3(0, 0, 1)
	);

	Triangle tri
	{
		Vector3(-1, -1, 10),
		Vector3(1, -1, 10),
		Vector3(0, 1, 10),
	};

	EXPECT_FLOAT_EQ(r.Intersects(tri), 10.0f);
}

TEST(IntersectionTests, Ray_Triangle7)
{
	// Ray intersects triangle at an angle - ray aimed at triangle center
	// Reuse triangle from Ray_Triangle1 which we know works
	Triangle tri
	{
		Vector3(-1, -1, 10),
		Vector3(1, -1, 10),
		Vector3(0, 1, 10),
	};

	// Shoot ray from side, aimed at triangle center (0, -1/3, 10)
	Ray r(
		Vector3(-5, 0, 0),
		Vector3::Normalize(Vector3(5, -0.33f, 10))
	);

	float distance = r.Intersects(tri);
	EXPECT_FALSE(std::isnan(distance));
	EXPECT_GT(distance, 0.0f);
}

TEST(IntersectionTests, Ray_Sphere1)
{
	Ray r(
		Vector3::Zero(),
		Vector3::UnitZ()
	);

	BoundingSphere sph(
		Vector3(0.1, 0, 5),
		0.125f
	);

	EXPECT_FALSE(std::isnan(r.Intersects(sph)));
}

TEST(IntersectionTests, Ray_Sphere2)
{
	Ray r(
		Vector3::Zero(),
		Vector3::UnitZ()
	);

	BoundingSphere sph(
		Vector3::One(),
		0.5f
	);

	EXPECT_TRUE(std::isnan(r.Intersects(sph)));
}

TEST(IntersectionTests, Ray_Sphere3)
{
	// Ray starts inside the sphere - returns negative distance (behind origin)
	Ray r(
		Vector3(0, 0, 5),
		Vector3(0, 0, 1)
	);

	BoundingSphere sph(
		Vector3(0, 0, 5),
		2.0f
	);

	float distance = r.Intersects(sph);
	EXPECT_FALSE(std::isnan(distance));
	// When inside sphere, returns the closer intersection (behind the ray = negative)
	EXPECT_LT(distance, 0.0f);
}

TEST(IntersectionTests, Ray_Sphere4)
{
	// Ray passes through sphere center
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0, 0, 1)
	);

	BoundingSphere sph(
		Vector3(0, 0, 10),
		1.0f
	);

	EXPECT_FLOAT_EQ(r.Intersects(sph), 9.0f);
}

TEST(IntersectionTests, Ray_Sphere5)
{
	// Ray grazes the sphere (tangent)
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0, 0, 1)
	);

	BoundingSphere sph(
		Vector3(1.0f, 0, 10),
		1.0f
	);

	EXPECT_FLOAT_EQ(r.Intersects(sph), 10.0f);
}

TEST(IntersectionTests, Ray_Sphere6)
{
	// Ray intersects sphere at an angle
	Ray r(
		Vector3(0, 0, 0),
		Vector3(1, 1, 1).Normalize()
	);

	BoundingSphere sph(
		Vector3(5, 5, 5),
		2.0f
	);

	float distance = r.Intersects(sph);
	EXPECT_FALSE(std::isnan(distance));
	EXPECT_GT(distance, 0.0f);
	EXPECT_LT(distance, std::sqrt(75.0f)); // Distance to center
}

TEST(IntersectionTests, Ray_Sphere7)
{
	// Ray with sphere completely behind it
	Ray r(
		Vector3(0, 0, 20),
		Vector3(0, 0, 1)
	);

	BoundingSphere sph(
		Vector3(0, 0, 10),
		1.0f
	);

	float distance = r.Intersects(sph);
	// Implementation returns intersection even if behind ray origin
	EXPECT_FALSE(std::isnan(distance));
	EXPECT_LT(distance, 0.0f); // Negative distance indicates behind origin
}

TEST(IntersectionTests, Ray_Sphere8)
{
	// Ray origin at sphere surface
	Ray r(
		Vector3(0, 0, 9),
		Vector3(0, 0, 1)
	);

	BoundingSphere sph(
		Vector3(0, 0, 10),
		1.0f
	);

	float distance = r.Intersects(sph);
	EXPECT_FALSE(std::isnan(distance));
	EXPECT_NEAR(distance, 0.0f, 0.001f);
}

TEST(IntersectionTests, Ray_BoundingBox1)
{
	// Ray intersects box from the front
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0, 0, 1)
	);

	BoundingBox box(
		Vector3(-1, -1, 5),
		Vector3(2, 2, 2)
	);

	EXPECT_FLOAT_EQ(r.Intersects(box), 5.0f);
}

TEST(IntersectionTests, Ray_BoundingBox2)
{
	// Ray starts inside the box
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0, 0, 1)
	);

	BoundingBox box(
		Vector3(-1, -1, -1),
		Vector3(2, 2, 2)
	);

	EXPECT_FLOAT_EQ(r.Intersects(box), 0.0f);
}

TEST(IntersectionTests, Ray_BoundingBox3)
{
	// Ray misses the box
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0, 0, 1)
	);

	BoundingBox box(
		Vector3(5, 5, 5),
		Vector3(1, 1, 1)
	);

	EXPECT_TRUE(std::isnan(r.Intersects(box)));
}

TEST(IntersectionTests, Ray_BoundingBox4)
{
	// Ray points in opposite direction
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0, 0, -1)
	);

	BoundingBox box(
		Vector3(-1, -1, 5),
		Vector3(2, 2, 2)
	);

	EXPECT_TRUE(std::isnan(r.Intersects(box)));
}

TEST(IntersectionTests, Ray_BoundingBox5)
{
	// Ray intersects box at an angle
	Ray r(
		Vector3(0, 0, 0),
		Vector3(1, 1, 1).Normalize()
	);

	BoundingBox box(
		Vector3(4, 4, 4),
		Vector3(2, 2, 2)
	);

	float distance = r.Intersects(box);
	EXPECT_FALSE(std::isnan(distance));
	EXPECT_GT(distance, 0.0f);
}

TEST(IntersectionTests, Ray_BoundingBox6)
{
	// Ray intersects box centered at origin
	Ray r(
		Vector3(5, 0, 0),
		Vector3(-1, 0, 0)
	);

	BoundingBox box(
		Vector3(-1, -1, -1),
		Vector3(2, 2, 2)
	);

	EXPECT_FLOAT_EQ(r.Intersects(box), 4.0f);
}

TEST(IntersectionTests, Ray_BoundingPlane1)
{
	// Ray intersects plane perpendicular to its normal
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0, 0, 1)
	);

	// Plane at z = 10, normal pointing back towards ray
	BoundingPlane plane{
		Vector3(0, 0, 1),
		-10.0f
	};

	EXPECT_FLOAT_EQ(r.Intersects(plane), 10.0f);
}

TEST(IntersectionTests, Ray_BoundingPlane2)
{
	// Ray intersects plane at an angle
	Ray r(
		Vector3(0, 0, 0),
		Vector3(1, 0, 1).Normalize()
	);

	// Plane at z = 5, normal pointing in +Z
	BoundingPlane plane{
		Vector3(0, 0, 1),
		-5.0f
	};

	float distance = r.Intersects(plane);
	EXPECT_FALSE(std::isnan(distance));
	EXPECT_GT(distance, 0.0f);
}

TEST(IntersectionTests, Ray_BoundingPlane3)
{
	// Ray parallel to plane (no intersection)
	Ray r(
		Vector3(0, 0, 0),
		Vector3(1, 0, 0)
	);

	// Plane at z = 5, normal pointing in +Z
	BoundingPlane plane{
		Vector3(0, 0, 1),
		-5.0f
	};

	EXPECT_TRUE(std::isnan(r.Intersects(plane)));
}

TEST(IntersectionTests, Ray_BoundingPlane4)
{
	// Ray pointing away from plane
	Ray r(
		Vector3(0, 0, 0),
		Vector3(0, 0, -1)
	);

	// Plane at z = 10
	BoundingPlane plane{
		Vector3(0, 0, 1),
		-10.0f
	};

	EXPECT_TRUE(std::isnan(r.Intersects(plane)));
}

TEST(IntersectionTests, Ray_BoundingPlane5)
{
	// Ray starts on the plane (within epsilon threshold, returns NaN to avoid self-intersection)
	Ray r(
		Vector3(0, 0, 5),
		Vector3(0, 0, 1)
	);

	// Plane at z = 5
	BoundingPlane plane{
		Vector3(0, 0, 1),
		-5.0f
	};

	EXPECT_TRUE(std::isnan(r.Intersects(plane)));
}

TEST(IntersectionTests, Ray_BoundingPlane6)
{
	// Ray intersects vertical plane (YZ plane)
	Ray r(
		Vector3(-5, 0, 0),
		Vector3(1, 0, 0)
	);

	// Plane at x = 3 (normal pointing in +X direction)
	BoundingPlane plane{
		Vector3(1, 0, 0),
		-3.0f
	};

	EXPECT_FLOAT_EQ(r.Intersects(plane), 8.0f);
}

TEST(IntersectionTests, Ray_BoundingPlane7)
{
	// Ray intersects arbitrary oriented plane
	Ray r(
		Vector3(0, 0, 0),
		Vector3(1, 1, 1).Normalize()
	);

	// Plane with normal (1,1,1) passing through point (3,3,3)
	// Plane equation: x + y + z - 9 = 0
	// In form: Normal.X * x + Normal.Y * y + Normal.Z * z + D = 0
	// So D = -9
	BoundingPlane plane{
		Vector3(1, 1, 1).Normalize(),
		-9.0f / std::sqrt(3.0f)
	};

	float distance = r.Intersects(plane);
	EXPECT_FALSE(std::isnan(distance));
	EXPECT_NEAR(distance, std::sqrt(27.0f), 0.001f);
}


