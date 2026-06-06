#include "ViewingFrustum.hpp"
#include "BoundingSphere.hpp"
#include "BoundingBox.hpp"
#include "Ray.hpp"
#include <algorithm>
#include <limits>

namespace Engine3DRadSpace::Math
{
	ViewingFrustum::ViewingFrustum(const Matrix4x4& view, const Matrix4x4& projection)
	{
		Matrix4x4 viewProj = view * projection;

		// Extract frustum planes from the view-projection matrix
		// Left plane
		_planes[0].Normal.X = viewProj.M14 + viewProj.M11;
		_planes[0].Normal.Y = viewProj.M24 + viewProj.M21;
		_planes[0].Normal.Z = viewProj.M34 + viewProj.M31;
		_planes[0].D = viewProj.M44 + viewProj.M41;

		// Right plane
		_planes[1].Normal.X = viewProj.M14 - viewProj.M11;
		_planes[1].Normal.Y = viewProj.M24 - viewProj.M21;
		_planes[1].Normal.Z = viewProj.M34 - viewProj.M31;
		_planes[1].D = viewProj.M44 - viewProj.M41;

		// Bottom plane
		_planes[2].Normal.X = viewProj.M14 + viewProj.M12;
		_planes[2].Normal.Y = viewProj.M24 + viewProj.M22;
		_planes[2].Normal.Z = viewProj.M34 + viewProj.M32;
		_planes[2].D = viewProj.M44 + viewProj.M42;

		// Top plane
		_planes[3].Normal.X = viewProj.M14 - viewProj.M12;
		_planes[3].Normal.Y = viewProj.M24 - viewProj.M22;
		_planes[3].Normal.Z = viewProj.M34 - viewProj.M32;
		_planes[3].D = viewProj.M44 - viewProj.M42;

		// Near plane
		_planes[4].Normal.X = viewProj.M14 + viewProj.M13;
		_planes[4].Normal.Y = viewProj.M24 + viewProj.M23;
		_planes[4].Normal.Z = viewProj.M34 + viewProj.M33;
		_planes[4].D = viewProj.M44 + viewProj.M43;

		// Far plane
		_planes[5].Normal.X = viewProj.M14 - viewProj.M13;
		_planes[5].Normal.Y = viewProj.M24 - viewProj.M23;
		_planes[5].Normal.Z = viewProj.M34 - viewProj.M33;
		_planes[5].D = viewProj.M44 - viewProj.M43;

		// Normalize all planes
		for (int i = 0; i < 6; i++)
		{
			float length = _planes[i].Normal.Length();
			_planes[i].Normal /= length;
			_planes[i].D /= length;
		}

		// Calculate frustum corners
		Matrix4x4 invViewProj = Matrix4x4::Invert(viewProj);

		// Near plane corners (z = -1 in NDC)
		_corners[0] = Vector3::Transform(Vector3(-1, -1, -1), invViewProj);
		_corners[1] = Vector3::Transform(Vector3(1, -1, -1), invViewProj);
		_corners[2] = Vector3::Transform(Vector3(-1, 1, -1), invViewProj);
		_corners[3] = Vector3::Transform(Vector3(1, 1, -1), invViewProj);

		// Far plane corners (z = 1 in NDC)
		_corners[4] = Vector3::Transform(Vector3(-1, -1, 1), invViewProj);
		_corners[5] = Vector3::Transform(Vector3(1, -1, 1), invViewProj);
		_corners[6] = Vector3::Transform(Vector3(-1, 1, 1), invViewProj);
		_corners[7] = Vector3::Transform(Vector3(1, 1, 1), invViewProj);
	}

	BoundingPlane ViewingFrustum::Top()
	{
		return _planes[3];
	}

	BoundingPlane ViewingFrustum::Bottom()
	{
		return _planes[2];
	}

	BoundingPlane ViewingFrustum::Left()
	{
		return _planes[0];
	}

	BoundingPlane ViewingFrustum::Right()
	{
		return _planes[1];
	}

	BoundingPlane ViewingFrustum::Near()
	{
		return _planes[4];
	}

	BoundingPlane ViewingFrustum::Far()
	{
		return _planes[5];
	}

	std::array<Vector3, 8> ViewingFrustum::Corners()
	{
		return _corners;
	}

	bool ViewingFrustum::Contains(const Vector3& point)
	{
		for (int i = 0; i < 6; i++)
		{
			float distance = Vector3::Dot(_planes[i].Normal, point) + _planes[i].D;
			if (distance < 0)
				return false;
		}
		return true;
	}

	bool ViewingFrustum::Contains(const BoundingSphere& sphere)
	{
		for (int i = 0; i < 6; i++)
		{
			float distance = Vector3::Dot(_planes[i].Normal, sphere.Center) + _planes[i].D;
			if (distance < -sphere.Radius)
				return false;
		}
		return true;
	}

	bool ViewingFrustum::Contains(const BoundingBox& box)
	{
		Vector3 corners[8] = {
			box.Position,
			box.Position + Vector3(box.Scale.X, 0, 0),
			box.Position + Vector3(0, box.Scale.Y, 0),
			box.Position + Vector3(box.Scale.X, box.Scale.Y, 0),
			box.Position + Vector3(0, 0, box.Scale.Z),
			box.Position + Vector3(box.Scale.X, 0, box.Scale.Z),
			box.Position + Vector3(0, box.Scale.Y, box.Scale.Z),
			box.Position + box.Scale
		};

		for (int i = 0; i < 8; i++)
		{
			if (!Contains(corners[i]))
				return false;
		}
		return true;
	}

	bool ViewingFrustum::Contains(const BoundingPlane& plane)
	{
		for (int i = 0; i < 8; i++)
		{
			if (!plane.Contains(_corners[i]))
				return false;
		}
		return true;
	}

	bool ViewingFrustum::Contains(const ViewingFrustum& frustum)
	{
		auto otherCorners = frustum._corners;
		for (const auto& corner : otherCorners)
		{
			if (!Contains(corner))
				return false;
		}
		return true;
	}

	float ViewingFrustum::Intersects(const Ray& ray)
	{
		float tMin = -std::numeric_limits<float>::max();
		float tMax = std::numeric_limits<float>::max();

		for (int i = 0; i < 6; i++)
		{
			float denom = Vector3::Dot(_planes[i].Normal, ray.Direction);
			float dist = Vector3::Dot(_planes[i].Normal, ray.Origin) + _planes[i].D;

			if (std::abs(denom) < 1e-6f)
			{
				if (dist < 0)
					return -1.0f;
			}
			else
			{
				float t = -dist / denom;
				if (denom > 0)
				{
					tMin = std::max(tMin, t);
				}
				else
				{
					tMax = std::min(tMax, t);
				}

				if (tMin > tMax)
					return -1.0f;
			}
		}

		return tMin >= 0 ? tMin : (tMax >= 0 ? 0.0f : -1.0f);
	}
}