#include "Legacy.hpp"
#include <Engine3DRadSpace/Objects/Impl/Objects.hpp>
#include <Engine3DRadSpace/Objects/Impl/TextPrint.hpp>
#include <Engine3DRadSpace/Objects/ObjectList.hpp>
#include <Engine3DRadSpace/Physics/Objects/RigidDynamic.hpp>
#include <Engine3DRadSpace/Physics/Objects/RigidStatic.hpp>
#include <Engine3DRadSpace/Projects/Serialization.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;
using namespace Engine3DRadSpace::Projects;

static ObjectList *objList;
static std::filesystem::path projectPath;

void Engine3DRadSpace::Legacy::SetObjectList(ObjectList *list)
{
	objList = list;
}

void Engine3DRadSpace::Legacy::SetProjectPath(const std::filesystem::path &path)
{
	projectPath = std::filesystem::path(path);
}

void iObjectStart(unsigned obj_x)
{
	(*objList)[obj_x]->Enable();
}

void iObjectStop(unsigned obj_x)
{
	(*objList)[obj_x]->Disable();
}

void iObjectSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->Switch();

}

void iObjectShow(unsigned obj_x)
{
	(*objList)[obj_x]->Show();
}

void iObjectHide(unsigned obj_x)
{
	(*objList)[obj_x]->Hide();
}

void iObjectShowHideSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->SwitchVisibility();
}

void iObjectReset(unsigned obj_x)
{
	auto obj = Serializer::LoadObjectFromProject(projectPath, obj_x);
	objList->Replace(obj, obj_x);
	delete obj;
}

void iObjectOrientation(unsigned obj_x, Quaternion& q)
{
	auto refobj = (*objList)[obj_x];
	if(auto obj = dynamic_cast<IObject3D*>(refobj); obj != nullptr)
	{
		q = obj->Rotation;
		return;
	}
	if(auto obj = dynamic_cast<IObject2D*>(refobj); obj != nullptr)
	{
		auto r = obj->Rotation;
		q = Quaternion(r, r, r, r);
		return;
	}
	q = Quaternion();
}

void iObjectOrientationSet(unsigned obj_x, const Quaternion& q)
{
	auto refobj = (*objList)[obj_x];
	if(auto obj = dynamic_cast<IObject3D*>(refobj); obj != nullptr) obj->Rotation = q;
	if(auto obj = dynamic_cast<IObject2D*>(refobj); obj != nullptr) obj->Rotation = q.X;
}

void iObjectOrientationReset(unsigned obj_x, Quaternion& q)
{
	std::unique_ptr<IObject> temp;
	temp.reset(Serializer::LoadObjectFromProject(projectPath, obj_x));

	if(auto refobj_lst = dynamic_cast<IObject3D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject3D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		q = refobj_lst->Rotation = temp_obj->Rotation;
		return;
	}

	if(auto refobj_lst = dynamic_cast<IObject2D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject2D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		float theta = refobj_lst->Rotation = temp_obj->Rotation;
		q = Quaternion(theta, theta, theta, theta);
		return;
	}
}

void iObjectLocation(unsigned obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Position;
	else v = Vector3();
}

void iObjectLocationSet(unsigned obj_x, const Vector3& v)
{
	auto refobj = (*objList)[obj_x];
	if(auto obj = dynamic_cast<IObject3D*>(refobj); obj != nullptr) obj->Position = v;
	if(auto obj = dynamic_cast<IObject2D*>(refobj); obj != nullptr) obj->Position = Vector2(v.X, v.Y);
}

void iObjectLocationReset(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v)
{
	std::unique_ptr<IObject> temp;
	temp.reset(Serializer::LoadObjectFromProject(projectPath, obj_x));

	if(auto refobj_lst = dynamic_cast<IObject3D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject3D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		v = refobj_lst->Position = temp_obj->Position;
	}
}

void iObjectPositionReset(unsigned obj_x, Engine3DRadSpace::Math::Quaternion& outRotation, Engine3DRadSpace::Math::Vector3& outLocation)
{
	std::unique_ptr<IObject> temp;
	temp.reset(Serializer::LoadObjectFromProject(projectPath, obj_x));
	if(auto refobj_lst = dynamic_cast<IObject3D*>((*objList)[obj_x]), temp_obj = dynamic_cast<IObject3D*>(temp.get()); refobj_lst != nullptr && temp_obj != nullptr)
	{
		outLocation = refobj_lst->Position = temp_obj->Position;
		outRotation = refobj_lst->Rotation = temp_obj->Rotation;
	}
}

void iObjectScaleSet(unsigned obj_x, const Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) obj->Scale = v;
}

void iObjectScale(unsigned obj_x, Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr) v = obj->Scale;
	else v = Math::Vector3();
}

float iObjectKmh(unsigned obj_x)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		auto vel = obj->GetLinearVelocity();
		return vel.Length() * 3.6f;
	}
	else return 0.0f;
}

void iObjectVelocity(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		 v = obj->GetLinearVelocity();
	}
	else v = Vector3::Zero();
}

void iObjectVelocitySet(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->SetLinearVelocity(v);
	}
}

void iObjectSpin(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		 v = obj->GetAngularVelocity();
	}
	else v = Vector3::Zero();
}

void iObjectSpinSet(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->SetAngularVelocity(v);
	}
}

void iObjectTorqueApply(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr) obj->GetCollider()->ApplyTorque(v);
}

void iObjectAngularAccelerationApply(unsigned obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if (obj != nullptr) obj->GetCollider()->ApplyAngularAcceleration(v);
}

void iObjectForceApply(unsigned ojb_x, Math::Vector3 f, Math::Vector3* p)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[ojb_x]);
	if(obj != nullptr)
	{
		if(p == nullptr)
			obj->GetCollider()->ApplyForce(f);
		else
			obj->GetCollider()->ApplyForce(f, *p);
	}
}

void iObjectAccelerationApply(unsigned obj_x, const Math::Vector3& acc)
{
	auto obj = dynamic_cast<RigidDynamic*>((*objList)[obj_x]);
	if(obj != nullptr) obj->GetCollider()->ApplyAcceleration(acc);
}

void iObjectDampingApply(unsigned obj_x, Math::Vector3& v, bool is_rotation, bool local_axis)
{
	auto obj = dynamic_cast<RigidStatic*>((*objList)[obj_x]);
	obj->SetLinearDamping(v.X);
}

float iObjectPicked(unsigned obj_x, const Math::Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		return 0;
	}
	else return -std::numeric_limits<float>::infinity();
}

int iObjectScan(
	unsigned obj_x, 
	const Math::Vector3& origin,
	const Math::Vector3& direction,
	float radius,
	Math::Vector3& contactPoint, 
	Math::Vector3& contactNormal)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		auto intersection = obj->Intersects(
			Ray{
				.Origin = origin,
				.Direction = direction
			}
		);
		if (!std::isnan(intersection))
		{
			float d = intersection;
			if (d > radius) return false;
			else
			{
				contactPoint = origin + (d * direction);
				contactNormal = -direction;
				return true;
			}
		}
		else return false;
	}
	else return false;
}

void iObjectTextSet(unsigned obj_x, const std::string &str)
{
	auto txtPrint = dynamic_cast<TextPrint*>((*objList)[obj_x]);
	if(txtPrint != nullptr) txtPrint->Text = str;
}

void iObjectParamSet(unsigned obj_x, int index, float t)
{
	auto obj = (*objList)[obj_x];
	if (obj == nullptr) return;

	auto uuid = obj->GetUUID();
	if (uuid == Reflection::UUID{}) return;

	auto refl = Internal::GetReflDataFromUUID(uuid);
	if (refl->NumFields() > index) return;
	if (refl == nullptr) return;

	auto field = refl->operator[](index);

	if(field->TypeHash() == typeid(float).hash_code())
	{
		field->Set(obj, &t);
	}
}

void iObjectRefresh(unsigned obj_x, const std::string& path)
{
	auto obj = (*objList)[obj_x];
	obj->Load(path);
}

int iStringLen(const std::string &str)
{
	return str.length();
}

void iStringUCase(const std::string &in, std::string &out)
{
	out = in;

	std::transform(in.begin(), in.end(), out.begin(),
	[](char c) -> char
	{
		return std::tolower(c);
	});
}

void iStringLCase(const std::string& in, std::string& out)
{
	out = in;

	std::transform(in.begin(), in.end(), out.begin(),
	[](char c) -> char
	{
		return std::tolower(c);
	});
}

//void iShaderSet(unsigned obj_x, const std::string& path)
//{
//	auto obj = dynamic_cast<Skinmesh*>((*objList)[obj_x]);
//	for (auto& mesh : *obj->GetModel())
//	{
//		for (auto& meshPart : *mesh)
//		{
//			
//		}
//	}
//}