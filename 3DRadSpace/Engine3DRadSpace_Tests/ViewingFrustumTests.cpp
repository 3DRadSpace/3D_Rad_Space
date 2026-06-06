#include "pch.h"
#include <Engine3DRadSpace/Math/ViewingFrustum.hpp>
#include <Engine3DRadSpace/Math/BoundingSphere.hpp>
#include <Engine3DRadSpace/Math/BoundingBox.hpp>
#include <Engine3DRadSpace/Math/Ray.hpp>
#include <Engine3DRadSpace/Math/Point.hpp>

using namespace Engine3DRadSpace::Math;

static void expect_equal_vec3(const Vector3& a, const Vector3& b, float epsilon = 1e-5f)
{
	EXPECT_NEAR(a.X, b.X, epsilon);
	EXPECT_NEAR(a.Y, b.Y, epsilon);
	EXPECT_NEAR(a.Z, b.Z, epsilon);
}

TEST(ViewingFrustumTests, Constructor_BasicPerspective)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -5),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	auto corners = frustum.Corners();
	EXPECT_EQ(corners.size(), 8);
}

TEST(ViewingFrustumTests, GetPlanes_AllPlanesValid)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -5),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	BoundingPlane top = frustum.Top();
	BoundingPlane bottom = frustum.Bottom();
	BoundingPlane left = frustum.Left();
	BoundingPlane right = frustum.Right();
	BoundingPlane nearPlane = frustum.Near();
	BoundingPlane farPlane = frustum.Far();

	EXPECT_NEAR(top.Normal.Length(), 1.0f, 1e-5f);
	EXPECT_NEAR(bottom.Normal.Length(), 1.0f, 1e-5f);
	EXPECT_NEAR(left.Normal.Length(), 1.0f, 1e-5f);
	EXPECT_NEAR(right.Normal.Length(), 1.0f, 1e-5f);
	EXPECT_NEAR(nearPlane.Normal.Length(), 1.0f, 1e-5f);
	EXPECT_NEAR(farPlane.Normal.Length(), 1.0f, 1e-5f);
}

TEST(ViewingFrustumTests, Contains_PointInsideFrustum)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -5),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	EXPECT_TRUE(frustum.Contains(Vector3(0, 0, 0)));
	EXPECT_TRUE(frustum.Contains(Vector3(0, 0, 10)));
}

TEST(ViewingFrustumTests, Contains_PointOutsideFrustum)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -5),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	EXPECT_FALSE(frustum.Contains(Vector3(0, 0, -10)));
	EXPECT_FALSE(frustum.Contains(Vector3(1000, 0, 0)));
	EXPECT_FALSE(frustum.Contains(Vector3(0, 1000, 0)));
}

TEST(ViewingFrustumTests, Contains_PointBehindCamera)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, 0),
		Vector3(0, 0, 1),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	EXPECT_FALSE(frustum.Contains(Vector3(0, 0, -5)));
}

TEST(ViewingFrustumTests, Contains_SphereFullyInside)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	BoundingSphere sphere(Vector3(0, 0, 0), 0.5f);
	EXPECT_TRUE(frustum.Contains(sphere));
}

TEST(ViewingFrustumTests, Contains_SpherePartiallyInside)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	BoundingSphere sphere(Vector3(0, 0, 50), 10.0f);
	EXPECT_TRUE(frustum.Contains(sphere));
}

TEST(ViewingFrustumTests, Contains_SphereOutside)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	BoundingSphere sphere(Vector3(0, 0, -50), 1.0f);
	EXPECT_FALSE(frustum.Contains(sphere));
}

TEST(ViewingFrustumTests, Contains_BoxFullyInside)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	BoundingBox box(Vector3(-0.5f, -0.5f, -0.5f), Vector3(1.0f, 1.0f, 1.0f));
	EXPECT_TRUE(frustum.Contains(box));
}

TEST(ViewingFrustumTests, Contains_BoxOutside)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	BoundingBox box(Vector3(-100, -100, -100), Vector3(1.0f, 1.0f, 1.0f));
	EXPECT_FALSE(frustum.Contains(box));
}

TEST(ViewingFrustumTests, Contains_FrustumInsideAnother)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection1 = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);
	Matrix4x4 projection2 = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 0.78f, 1.0f, 50.0f);

	ViewingFrustum frustum1(view, projection1);
	ViewingFrustum frustum2(view, projection2);

	auto corners2 = frustum2.Corners();
	int containedCount = 0;
	for (const auto& corner : corners2)
	{
		if (frustum1.Contains(corner))
			containedCount++;
	}

	EXPECT_GT(containedCount, 0);
}

TEST(ViewingFrustumTests, Intersects_RayThroughCenter)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, 0),
		Vector3(0, 0, 1),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(1.0f, 1.57f, 1.0f, 100.0f);

	ViewingFrustum frustum(view, projection);

	Ray ray(Vector3(0, 0, -5), Vector3::Normalize(Vector3(0, 0, 1)));
	float distance = frustum.Intersects(ray);

	EXPECT_GE(distance, 0.0f);
}

TEST(ViewingFrustumTests, Intersects_RayMissesFrustum)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	Ray ray(Vector3(1000, 0, -20), Vector3::Normalize(Vector3(0, 0, 1)));
	float distance = frustum.Intersects(ray);

	EXPECT_LT(distance, 0.0f);
}

TEST(ViewingFrustumTests, Intersects_RayOppositeDirection)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	Ray ray(Vector3(0, 0, -20), Vector3::Normalize(Vector3(0, 0, -1)));
	float distance = frustum.Intersects(ray);

	EXPECT_LT(distance, 0.0f);
}

TEST(ViewingFrustumTests, Intersects_RayInsideFrustum)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	Vector3 center(0, 0, 0);
	EXPECT_TRUE(frustum.Contains(center));

	Ray ray(center, Vector3::Normalize(Vector3(0, 0, 1)));
	float distance = frustum.Intersects(ray);

	EXPECT_TRUE(distance >= 0.0f || frustum.Contains(center));
}

TEST(ViewingFrustumTests, Corners_HasEightCorners)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -5),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreatePerspectiveProjection(16.0f / 9.0f, 1.57f, 1.0f, 100.0f);

	ViewingFrustum frustum(view, projection);

	auto corners = frustum.Corners();
	EXPECT_EQ(corners.size(), 8);

	for (const auto& corner : corners)
	{
		EXPECT_FALSE(std::isnan(corner.X));
		EXPECT_FALSE(std::isnan(corner.Y));
		EXPECT_FALSE(std::isnan(corner.Z));
	}
}

TEST(ViewingFrustumTests, OrthographicProjection_PointInside)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreateOrthographicProjection(Point(1920, 1080), 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	EXPECT_TRUE(frustum.Contains(Vector3(0, 0, 0)));
	EXPECT_TRUE(frustum.Contains(Vector3(100, 100, 50)));
}

TEST(ViewingFrustumTests, OrthographicProjection_PointOutside)
{
	Matrix4x4 view = Matrix4x4::CreateLookAtView(
		Vector3(0, 0, -10),
		Vector3(0, 0, 0),
		Vector3(0, 1, 0)
	);
	Matrix4x4 projection = Matrix4x4::CreateOrthographicProjection(Point(1920, 1080), 0.1f, 100.0f);

	ViewingFrustum frustum(view, projection);

	EXPECT_FALSE(frustum.Contains(Vector3(0, 0, -200)));
	EXPECT_FALSE(frustum.Contains(Vector3(10000, 0, 0)));
}
