#include "IDynamicCollider.h"
#include "../../Physics/IDynamicCollider.hpp"
#include "../../Math/BoundingBox.hpp"
#include "../../Math/BoundingSphere.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;

float E3DRSP_IDynamicCollider_GetAngularDamping(E3DRSP_IDynamicCollider collider)
{
	if (collider == nullptr) return 0.0f;
	return static_cast<IDynamicCollider*>(collider)->GetAngularDamping();
}

void E3DRSP_IDynamicCollider_SetAngularDamping(E3DRSP_IDynamicCollider collider, float angularDamping)
{
	if (collider == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->SetAngularDamping(angularDamping);
}

E3DRSP_Vector3 E3DRSP_IDynamicCollider_GetLinearVelocity(E3DRSP_IDynamicCollider collider)
{
	if (collider == nullptr) return E3DRSP_Vector3{ 0.0f, 0.0f, 0.0f };
	auto velocity = static_cast<IDynamicCollider*>(collider)->GetLinearVelocity();
	return E3DRSP_Vector3{ velocity.X, velocity.Y, velocity.Z };
}

void E3DRSP_IDynamicCollider_SetLinearVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* linearVelocity)
{
	if (collider == nullptr || linearVelocity == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->SetLinearVelocity(Vector3(linearVelocity->X, linearVelocity->Y, linearVelocity->Z));
}

E3DRSP_Vector3 E3DRSP_IDynamicCollider_GetAngularVelocity(E3DRSP_IDynamicCollider collider)
{
	if (collider == nullptr) return E3DRSP_Vector3{ 0.0f, 0.0f, 0.0f };
	auto velocity = static_cast<IDynamicCollider*>(collider)->GetAngularVelocity();
	return E3DRSP_Vector3{ velocity.X, velocity.Y, velocity.Z };
}

void E3DRSP_IDynamicCollider_SetAngularVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* angularVelocity)
{
	if (collider == nullptr || angularVelocity == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->SetAngularVelocity(Vector3(angularVelocity->X, angularVelocity->Y, angularVelocity->Z));
}

E3DRSP_Vector3 E3DRSP_IDynamicCollider_GetMaxAngularVelocity(E3DRSP_IDynamicCollider collider)
{
	if (collider == nullptr) return E3DRSP_Vector3{ 0.0f, 0.0f, 0.0f };
	auto velocity = static_cast<IDynamicCollider*>(collider)->GetMaxAngularVelocity();
	return E3DRSP_Vector3{ velocity.X, velocity.Y, velocity.Z };
}

void E3DRSP_IDynamicCollider_SetMaxAngularVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* linearVelocity)
{
	if (collider == nullptr || linearVelocity == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->SetMaxAngularVelocity(Vector3(linearVelocity->X, linearVelocity->Y, linearVelocity->Z));
}

void E3DRSP_IDynamicCollider_AttachShapeBox(E3DRSP_IDynamicCollider collider, const E3DRSP_BoundingBox* box)
{
	if (collider == nullptr || box == nullptr) return;
	BoundingBox bbox(Vector3(box->Position.X, box->Position.Y, box->Position.Z), Vector3(box->Scale.X, box->Scale.Y, box->Scale.Z));
	static_cast<IDynamicCollider*>(collider)->AttachShape(bbox);
}

void E3DRSP_IDynamicCollider_AttachShapeSphere(E3DRSP_IDynamicCollider collider, const E3DRSP_BoundingSphere* sphere)
{
	if (collider == nullptr || sphere == nullptr) return;
	BoundingSphere bsphere(Vector3(sphere->Center.X, sphere->Center.Y, sphere->Center.Z), sphere->Radius);
	static_cast<IDynamicCollider*>(collider)->AttachShape(bsphere);
}

void E3DRSP_IDynamicCollider_UpdateMassAndInertia(E3DRSP_IDynamicCollider collider)
{
	if (collider == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->UpdateMassAndInertia();
}

void E3DRSP_IDynamicCollider_ApplyForce(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* force)
{
	if (collider == nullptr || force == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->ApplyForce(Vector3(force->X, force->Y, force->Z));
}

void E3DRSP_IDynamicCollider_ApplyForceAtCenter(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* force, const E3DRSP_Vector3* center)
{
	if (collider == nullptr || force == nullptr || center == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->ApplyForce(Vector3(force->X, force->Y, force->Z), Vector3(center->X, center->Y, center->Z));
}

void E3DRSP_IDynamicCollider_ApplyTorque(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* force)
{
	if (collider == nullptr || force == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->ApplyTorque(Vector3(force->X, force->Y, force->Z));
}

void E3DRSP_IDynamicCollider_ApplyAcceleration(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* acc)
{
	if (collider == nullptr || acc == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->ApplyAcceleration(Vector3(acc->X, acc->Y, acc->Z));
}

void E3DRSP_IDynamicCollider_ApplyAngularAcceleration(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* acc)
{
	if (collider == nullptr || acc == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->ApplyAngularAcceleration(Vector3(acc->X, acc->Y, acc->Z));
}

void E3DRSP_IDynamicCollider_SetKinematic(E3DRSP_IDynamicCollider collider, bool isKinematic)
{
	if (collider == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->SetKinematic(isKinematic);
}

void E3DRSP_IDynamicCollider_AddLinearVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* v)
{
	if (collider == nullptr || v == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->AddLinearVelocity(Vector3(v->X, v->Y, v->Z));
}

void E3DRSP_IDynamicCollider_AddAngularVelocity(E3DRSP_IDynamicCollider collider, const E3DRSP_Vector3* v)
{
	if (collider == nullptr || v == nullptr) return;
	static_cast<IDynamicCollider*>(collider)->AddAngularVelocity(Vector3(v->X, v->Y, v->Z));
}

void E3DRSP_IDynamicCollider_Destroy(E3DRSP_IDynamicCollider collider)
{
	if (collider == nullptr) return;
	delete static_cast<IDynamicCollider*>(collider);
}
