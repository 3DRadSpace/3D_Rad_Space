#include "ICamera.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

ICamera::ICamera(
	const Math::Vector3& normal,
	float aspectRatio,
	float fov,
	float npd,
	float fpd
) :
	Normal(normal),
	AspectRatio(aspectRatio),
	FieldOfView(fov),
	NearPlaneDistance(npd),
	FarPlaneDistance(fpd)
{
}

ViewingFrustum ICamera::GetViewingFrustum() const
{
	ViewingFrustum frustum(GetViewMatrix(), GetProjectionMatrix());
	return frustum;
}