#pragma once
#include "ObjectList.hpp"

/*
	Set of legacy functions from the old engine. Source: https://3drad.boards.net/page/script-reference
*/

namespace Engine3DRadSpace::Legacy
{
	//Sets the global state, since a list of objects is required.
	void DLLEXPORT SetObjectList(ObjectList* list);

	void DLLEXPORT iObjectStart(unsigned obj_x);
	void DLLEXPORT iObjectStop(unsigned obj_x);
	void DLLEXPORT iObjectSwitch(unsigned obj_x);
	void DLLEXPORT iObjectShow(unsigned obj_x);
	void DLLEXPORT iObjectHide(unsigned obj_x);
	void DLLEXPORT iObjectShowHideSwitch(unsigned obj_x);
	//void iObjectReset(OBJ_X)
	void DLLEXPORT iObjectOrientation(int obj_x, Math::Quaternion& q);
	void DLLEXPORT iObjectOrientationSet(int obj_x, const Math::Quaternion& q);
	//void iObjectOrientationReset(OBJ_X,Quaternion)
	void DLLEXPORT iObjectLocation(int obj_x, Math::Vector3& v);
	void DLLEXPORT iObjectLocationSet(int obj_x,const Math::Vector3 &v);
	//void iObjectLocationReset(OBJ_X,Vector3)
	//void iObjectPositionReset(OBJ_X,Quaternion,Vector3)
	void DLLEXPORT iObjectScaleSet(int obj_x, const Math::Vector3& v);
	void DLLEXPORT iObjectScale(int obj_x, Math::Vector3& v);
	//float iObjectKmh(OBJ_X)
	//iObjectVelocity(OBJ_X,Vector3)
	//iObjectVelocitySet(OBJ_X,Vector3)
	//iObjectSpin(OBJ_X,Vector3)
	//iObjectSpinSet(OBJ_X,Vector3)
	//iObjectTorqueApply(OBJ_X,Vector3) 
	//iObjectAngularAccelerationApply(OBJ_X,Vector3) 
	//iObjectForceApply(OBJ_X,Vector3,Vector3) 
	//iObjectAccelerationApply(OBJ_X,Vector3) 
	//iObjectDampingApply(OBJ_X,float,float,float,bool,bool) 
	//float iObjectPicked(OBJ_X, Vector3)
	//int iObjectScan(OBJ_X,Vector3,Vector3,float,Vector3,Vector3)
	//iObjectTextSet(OBJ_X,string)
	//iObjectParamSet(OBJ_X,int,float)
	void DLLEXPORT iObjectRefresh(int obj_x, const std::filesystem::path &path);
}