#include "ICollider.h"
#include "../../Physics/ICollider.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;

float E3DRSP_ICollider_GetMass(E3DRSP_ICollider* collider)
{
	return reinterpret_cast<ICollider*>(collider)->GetMass();
}

void E3DRSP_ICollider_SetMass(E3DRSP_ICollider* collider, float mass)
{
	reinterpret_cast<ICollider*>(collider)->SetMass(mass);
}

E3DRSP_Vector3 E3DRSP_ICollider_GetPosition(E3DRSP_ICollider* collider)
{
	if (collider == nullptr) return E3DRSP_Vector3{ 0.0f, 0.0f, 0.0f };
	auto pos = reinterpret_cast<ICollider*>(collider)->GetPosition();
	return E3DRSP_Vector3{ pos.X, pos.Y, pos.Z };
}

void E3DRSP_ICollider_SetPosition(E3DRSP_ICollider* collider, const E3DRSP_Vector3* position)
{
	if (collider == nullptr || position == nullptr) return;
	reinterpret_cast<ICollider*>(collider)->SetPosition(Vector3(position->X, position->Y, position->Z));
}

E3DRSP_Quaternion E3DRSP_ICollider_GetRotation(E3DRSP_ICollider* collider)
{
	if (collider == nullptr) return E3DRSP_Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
	auto rot = reinterpret_cast<ICollider*>(collider)->GetRotation();
	return E3DRSP_Quaternion{ rot.X, rot.Y, rot.Z, rot.W };
}

void E3DRSP_ICollider_SetRotation(E3DRSP_ICollider* collider, const E3DRSP_Quaternion* rotation)
{
	if (collider == nullptr || rotation == nullptr) return;
	reinterpret_cast<ICollider*>(collider)->SetRotation(Quaternion(rotation->X, rotation->Y, rotation->Z, rotation->W));
}

E3DRSP_IPhysicsEngine E3DRSP_ICollider_GetPhysics(const E3DRSP_ICollider* collider)
{
	return reinterpret_cast<const ICollider*>(collider)->GetPhysics();
}

float E3DRSP_ICollider_Intersects(E3DRSP_ICollider* collider, const E3DRSP_Ray* r)
{
	auto dst = reinterpret_cast<ICollider*>(collider)->Intersects(
		Ray
		{
			.Origin = Vector3{r->Origin.X, r->Origin.Y, r->Origin.Z},
			.Direction = Vector3{r->Direction.X, r->Direction.Y, r->Direction.Z}
		}
	);

	return dst.has_value() ? dst.value() : std::numeric_limits<float>::signaling_NaN();
}

void E3DRSP_ICollider_UpdateTransform(E3DRSP_ICollider* collider)
{
	if (collider == nullptr) return;
	reinterpret_cast<ICollider*>(collider)->UpdateTransform();
}

void E3DRSP_ICollider_UpdateTransform2(E3DRSP_ICollider* collider, const E3DRSP_Vector3* position, const E3DRSP_Quaternion* rotation)
{
	if (collider == nullptr || position == nullptr || rotation == nullptr) return;
	reinterpret_cast<ICollider*>(collider)->UpdateTransform(
		Vector3(position->X, position->Y, position->Z),
		Quaternion(rotation->X, rotation->Y, rotation->Z, rotation->W)
	);
}

void E3DRSP_ICollider_Destroy(E3DRSP_ICollider* collider)
{
	delete reinterpret_cast<ICollider*>(collider);
}