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
	float DLLEXPORT iObjectKmh(int obj_x);
	void DLLEXPORT iObjectVelocity(int obj_x, Math::Vector3& v);
	void DLLEXPORT iObjectVelocitySet(int obj_x, Math::Vector3& v);
	void DLLEXPORT iObjectSpin(int obj_x, Math::Vector3& v);
	void DLLEXPORT iObjectSpinSet(int obj_x, Math::Vector3& v);
	void DLLEXPORT iObjectTorqueApply(int obj_x, Math::Vector3& v);
	//void DLLEXPORT iObjectAngularAccelerationApply(int obj_x, Math::Vector3& v);
	//void DLLEXPORT iObjectForceApply(int ojb_x ,Vector3,Vector3) 
	//iObjectAccelerationApply(OBJ_X,Vector3) 
	//iObjectDampingApply(OBJ_X,float,float,float,bool,bool) 
	//float iObjectPicked(OBJ_X, Vector3)
	int iObjectScan(int obj_x,const Math::Vector3 &origin,const Math::Vector3 &direction, float radius, Math::Vector3& contactPoint, Math::Vector3& contactNormal);
	//iObjectTextSet(OBJ_X,string)
	//iObjectParamSet(OBJ_X,int,float)
	void DLLEXPORT iObjectRefresh(int obj_x, const std::filesystem::path &path);
	//int iObjectBonesCount(OBJ_X)
	//void iObjectBoneOrientation(OBJ_X,int,Quaternion,int)
	//iObjectBoneLocation(OBJ_X,int,Vector3,int)
	//void iObjectBoneOrientationSet(OBJ_X,int,Quaternion,int)\
	//iObjectBoneLocationSet(OBJ_X,int,Vector3)
	//iObjectBoneScaleSet(OBJ_X,int,Vector3)
	//iObjectEnvMapFocusSet(OBJ_X,Vector3)
	//iObjectImpostersCreate(OBJ_X,int)
	//iObjectImpostersDestroy(OBJ_X)
	//iObjectImposterSet(OBJ_X,int,Quaternion,Vector3)
	//iObjectImposterGet(OBJ_X,int,Quaternion,Vector3)
	//iObjectImposterScaleSet(OBJ_X,int,Vector3)
	//iObjectImposterHide(OBJ_X,int)
	//iObjectImposterShow(OBJ_X,int)
	//iObjectImposterShadowEnable(OBJ_X, int, bool)
	//iObjectImposterTorqueApply(OBJ_X,int,Vector3)
	//iObjectImposterAngularAccelerationApply(OBJ_X,int,Vector3)
	//iObjectImposterForceApply(OBJ_X,int,Vector3,Vector3)
	//iObjectImposterAccelerationApply(OBJ_X,int,Vector3) 
	//iObjectImposterVelocitySet(OBJ_X,int,Vector3)
	//iObjectChildTransform(OBJ_X, OBJ_Y, Vector3, Vector3)

	//void DLLEXPORT iShaderSet(int obj_x, const std::string& path);
	//iShaderStack(OBJ_X,string,float)
	//iShaderFloatSet(OBJ_X, string, float)
	//iShaderFloat2Set(OBJ_X,string,float,float)
	//iShaderFloat3Set(OBJ_X,string,float,float,float)
	//iShaderFloat4Set(OBJ_X,string,float,float,float,float)
	//iShaderFloat4x3Set(OBJ_X,string,float,float,float,float,float,float,float,float,float,float,float,float)
	//iShaderFloat4x4Set(OBJ_X,string,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float)
	//iShaderViewMatrixSet(OBJ_X, string, OBJ_Y)
	//iShaderProjectionMatrixSet(OBJ_X,string,OBJ_Y)
	//int iShaderTextureCreate(string)
	//iShaderTextureDestroy(int)
	//iShaderTextureSet(OBJ_X,string,int)

	//int iStringLen(const std::string)
	//void iStringUCase(string, string)
	//iStringLCase(string,string)
}