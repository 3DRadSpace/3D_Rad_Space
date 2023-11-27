#include "Legacy.hpp"

using namespace Engine3DRadSpace;

static ObjectList *objList;

void Engine3DRadSpace::Legacy::SetObjectList(ObjectList *list)
{
	objList = list;
}

void Engine3DRadSpace::Legacy::iObjectStart(unsigned obj_x)
{
	(*objList)[obj_x]->Enabled = true;
}

void Engine3DRadSpace::Legacy::iObjectStop(unsigned obj_x)
{
	(*objList)[obj_x]->Enabled = false;
}

void Engine3DRadSpace::Legacy::iObjectSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->Enabled = !((*objList)[obj_x]->Enabled);
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectShow(unsigned obj_x)
{
	(*objList)[obj_x]->Visible = true;
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectHide(unsigned obj_x)
{
	(*objList)[obj_x]->Visible = false;
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectShowHideSwitch(unsigned obj_x)
{
	(*objList)[obj_x]->Visible = !((*objList)[obj_x]->Visible);
}

void Engine3DRadSpace::Legacy::iObjectOrientation(int obj_x, Math::Quaternion& q)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		q = obj->Rotation;
	}
	else q = Math::Quaternion();
}

void Engine3DRadSpace::Legacy::iObjectOrientationSet(int obj_x, const Math::Quaternion& q)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Rotation = q;
	}
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectLocation(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		v = obj->Position;
	}
	else v = Math::Vector3();
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectLocationSet(int obj_x, const Math::Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Position = v;
	}
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectScaleSet(int obj_x, const Math::Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		obj->Scale = v;
	}
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectScale(int obj_x, Math::Vector3& v)
{
	auto obj = dynamic_cast<IObject3D*>((*objList)[obj_x]);
	if (obj != nullptr)
	{
		v = obj->Scale;
	}
	else v = Math::Vector3();
}

void DLLEXPORT Engine3DRadSpace::Legacy::iObjectRefresh(int obj_x, const std::filesystem::path& path)
{
}
