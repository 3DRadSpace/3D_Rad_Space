#pragma once
#include "../Engine3DRadSpace/Math/Vector3.hpp"
#include "../Engine3DRadSpace/Math/Quaternion.hpp"
#include "../Engine3DRadSpace/Objects/ObjectList.hpp"

/*
	Set of legacy functions from the old engine. Source: https://3drad.boards.net/page/script-reference
*/

namespace Engine3DRadSpace::Legacy
{
	//
	//Global state functions. As a end-user, ignore these two.
	//

	//Sets the global state, since a list of objects is required.
	void E3DRSP_SCRIPTING_EXPORT SetObjectList(Engine3DRadSpace::Objects::ObjectList* list);
	//Sets project file path used when resetting objects.
	void E3DRSP_SCRIPTING_EXPORT SetProjectPath(const std::filesystem::path &path);
}

extern "C"
{
	//
	//	Object functions.
	//

	void E3DRSP_SCRIPTING_EXPORT iObjectStart(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectStop(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectSwitch(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectShow(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectHide(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectShowHideSwitch(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectReset(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectOrientation(unsigned obj_x, Engine3DRadSpace::Math::Quaternion& q);
	void E3DRSP_SCRIPTING_EXPORT iObjectOrientationSet(unsigned obj_x, const Engine3DRadSpace::Math::Quaternion& q);
	void E3DRSP_SCRIPTING_EXPORT iObjectOrientationReset(unsigned obj_x, const Engine3DRadSpace::Math::Quaternion& q);
	void E3DRSP_SCRIPTING_EXPORT iObjectLocation(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectLocationSet(unsigned obj_x,const Engine3DRadSpace::Math::Vector3 &v);
	void E3DRSP_SCRIPTING_EXPORT iObjectLocationReset(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectPositionReset(
		unsigned OBJ_X,
		Engine3DRadSpace::Math::Quaternion& outRotation,
		Engine3DRadSpace::Math::Vector3& outLocation
	);
	void E3DRSP_SCRIPTING_EXPORT iObjectScaleSet(unsigned obj_x, const Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectScale(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	float E3DRSP_SCRIPTING_EXPORT iObjectKmh(unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iObjectVelocity(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectVelocitySet(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectSpin(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectSpinSet(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectTorqueApply(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectAngularAccelerationApply(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v);
	void E3DRSP_SCRIPTING_EXPORT iObjectForceApply(unsigned ojb_x, Engine3DRadSpace::Math::Vector3 f, Engine3DRadSpace::Math::Vector3 *p);
	void E3DRSP_SCRIPTING_EXPORT iObjectAccelerationApply(unsigned obj_x, const Engine3DRadSpace::Math::Vector3& acc);
	void E3DRSP_SCRIPTING_EXPORT iObjectDampingApply(unsigned obj_x, Engine3DRadSpace::Math::Vector3& v, bool is_rotation, bool local_axis);
	float E3DRSP_SCRIPTING_EXPORT iObjectPicked(unsigned obj_x, Engine3DRadSpace::Math::Vector3& outHitResult);
	int E3DRSP_SCRIPTING_EXPORT iObjectScan(
		unsigned obj_x,
		const Engine3DRadSpace::Math::Vector3 &origin,
		const Engine3DRadSpace::Math::Vector3 &direction,
		float radius,
		Engine3DRadSpace::Math::Vector3& contactPoint,
		Engine3DRadSpace::Math::Vector3& contactNormal
	);
	void E3DRSP_SCRIPTING_EXPORT iObjectTextSet(
		unsigned obj_x,
		const std::string& str
	);
	
	void E3DRSP_SCRIPTING_EXPORT iObjectParamSet(unsigned obj_x, int index, float t);
	void E3DRSP_SCRIPTING_EXPORT iObjectRefresh(unsigned obj_x, const std::string& path);
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
	void E3DRSP_SCRIPTING_EXPORT iObjectChildTransform(
		unsigned obj_x,
		unsigned obj_y,
		const Engine3DRadSpace::Math::Vector3& eulerAnglesAngularOffset,
		const Engine3DRadSpace::Math::Vector3& linearOffset
	);

	//void E3DRSP_SCRIPTING_EXPORT iShaderSet(int obj_x, const std::string& path);
	//void E3DRSP_SCRIPTING_EXPORT iShaderStack(int obj_x, const std::string& path, float rtScaleFactor);
	//void E3DRSP_SCRIPTING_EXPORT iShaderFloatSet(int obj_x, const std::string& name, float value);
	//void E3DRSP_SCRIPTING_EXPORT iShaderFloat2Set(int obj_x, const std::string& name, float x, float y);
	//void E3DRSP_SCRIPTING_EXPORT iShaderFloat3Set(int obj_x, const std::string& name, float x, float y, float z);
	//void E3DRSP_SCRIPTING_EXPORT iShaderFloat4Set(int obj_x, const std::string& name, float x, float y, float z, float w);
	/*
	void E3DRSP_SCRIPTING_EXPORT iShaderFloat4x3Set(
		int obj_x,
		const std::string& name,
		float m00, float m01, float m02, float m03, 
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23
	);
	*/
	/*
	void E3DRSP_SCRIPTING_EXPORT iShaderFloat4x4Set(
		int obj_x,
		const std::string& name,
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);
	*/
	//void E3DRSP_SCRIPTING_EXPORT iShaderViewMatrixSet(int obj_x, const std::string& name, int obj_y);
	//void E3DRSP_SCRIPTING_EXPORT iShaderProjectionMatrixSet(int obj_x, const std::string& name, int obj_y);
	//int E3DRSP_SCRIPTING_EXPORT iShaderTextureCreate(const std::string& name);
	//void E3DRSP_SCRIPTING_EXPORT iShaderTextureDestroy(int texture_id);
	//void E3DRSP_SCRIPTING_EXPORT iShaderTextureSet(int obj_x, const std::string& name, int texture_id);

	int E3DRSP_SCRIPTING_EXPORT iStringLen(const std::string &str);
	void E3DRSP_SCRIPTING_EXPORT iStringUCase(std::string &out, const std::string& in);
	void E3DRSP_SCRIPTING_EXPORT iStringLCase(std::string &out, const std::string &in);
	void E3DRSP_SCRIPTING_EXPORT iStringLeft(std::string& out, const std::string& in, int n);
	void E3DRSP_SCRIPTING_EXPORT iStringRight(std::string& out, const std::string& in, int n);
	void E3DRSP_SCRIPTING_EXPORT iStringMid(std::string& result, const std::string& in, int start, int length);
	void E3DRSP_SCRIPTING_EXPORT iStringStr(std::string& result, float, const std::string& format);
	float E3DRSP_SCRIPTING_EXPORT iStringVal(const std::string& str);
	size_t E3DRSP_SCRIPTING_EXPORT iStringFind(const std::string& str, const std::string& substr, int start, bool case_sensitive);
	void E3DRSP_SCRIPTING_EXPORT iStringReplace(
		std::string& result,
		const std::string& str,
		const std::string& old_substr,
		const std::string& new_substr,
		bool case_sensitive
	);

	void E3DRSP_SCRIPTING_EXPORT iPrint(const std::string& str, float x, float y, unsigned obj_x);
	void E3DRSP_SCRIPTING_EXPORT iGlobalStringSet(const std::string& str, int id);
	void E3DRSP_SCRIPTING_EXPORT iGlobalStringGet(std::string& out, int id);

	float E3DRSP_SCRIPTING_EXPORT iFloatRand(float a, float b);
	float E3DRSP_SCRIPTING_EXPORT iFloatAbs(float x);
	float E3DRSP_SCRIPTING_EXPORT iFloatSin(float x);
	float E3DRSP_SCRIPTING_EXPORT iFloatCos(float x);
	float E3DRSP_SCRIPTING_EXPORT iFloatSqrt(float x);
	float E3DRSP_SCRIPTING_EXPORT iFloatInterpolate(float x, float scrmin, float scrmax, float dstmin, float dstmax, bool clamp);
	/*
	Modes:
	Use 0 to reduce variation speed when closer to the target value.
	Use 1 to reduce variation speed when closer to the reference value.
	Use 2 to reduce variation speed when closer to the reference and target values.
	Use 3 to reduce variation speed when closer to the middle point between reference and target values.
	*/
	float E3DRSP_SCRIPTING_EXPORT iFloatTendTo(float adjust, float ref, float target, float speed, int mode);
	float E3DRSP_SCRIPTING_EXPORT iFloatTrend(float adjust, float ref, float target, float speed, int mode);
	float E3DRSP_SCRIPTING_EXPORT iVectorLength(const Engine3DRadSpace::Math::Vector3& vec);
	float E3DRSP_SCRIPTING_EXPORT iVectorLengthSq(const Engine3DRadSpace::Math::Vector3& vec);
	float E3DRSP_SCRIPTING_EXPORT iVectorLengthSet( Engine3DRadSpace::Math::Vector3& out, const Engine3DRadSpace::Math::Vector3& src, float length);
	float E3DRSP_SCRIPTING_EXPORT iVectorDot(const Engine3DRadSpace::Math::Vector3& a, const Engine3DRadSpace::Math::Vector3& b);
	void E3DRSP_SCRIPTING_EXPORT iVectorCross(
		Engine3DRadSpace::Math::Vector3& out,
		const Engine3DRadSpace::Math::Vector3& a,
		const Engine3DRadSpace::Math::Vector3& b
	);
	void E3DRSP_SCRIPTING_EXPORT iVectorRotate(
		Engine3DRadSpace::Math::Vector3& out,
		const Engine3DRadSpace::Math::Vector3& vec,
		const Engine3DRadSpace::Math::Quaternion& q
	);
	void E3DRSP_SCRIPTING_EXPORT iVectorEulerRotate(
		Engine3DRadSpace::Math::Vector3& out, 
		const Engine3DRadSpace::Math::Vector3& vec,
		float pitch,
		float yaw,
		float roll,
		const std::string& order
	);

	bool E3DRSP_SCRIPTING_EXPORT iVectorCompare(
		const Engine3DRadSpace::Math::Vector3& a,
		const Engine3DRadSpace::Math::Vector3& b,
		float tolerance
	);

	void E3DRSP_SCRIPTING_EXPORT iQuaternionFromAxisAngle(
		Engine3DRadSpace::Math::Quaternion& out,
		const Engine3DRadSpace::Math::Vector3& axis,
		float angle
	);

	void E3DRSP_SCRIPTING_EXPORT iQuaternionFromEulerAngles(
		Engine3DRadSpace::Math::Quaternion& out,
		float pitch,
		float yaw,
		float roll,
		const std::string& order
	);

	void E3DRSP_SCRIPTING_EXPORT iQuaternionToEulerAngles(
		const Engine3DRadSpace::Math::Quaternion& quat,
		float& pitch,
		float& yaw,
		float& roll
	);

	void E3DRSP_SCRIPTING_EXPORT iQuaternionLookAt(
		Engine3DRadSpace::Math::Quaternion& out,
		const Engine3DRadSpace::Math::Vector3& eye,
		const Engine3DRadSpace::Math::Vector3& target
	);

	void E3DRSP_SCRIPTING_EXPORT iQuaternionMultiply(
		Engine3DRadSpace::Math::Quaternion& out,
		const Engine3DRadSpace::Math::Quaternion& a,
		const Engine3DRadSpace::Math::Quaternion& b
	);

	void E3DRSP_SCRIPTING_EXPORT iQuaternionInterpolate(
		Engine3DRadSpace::Math::Quaternion& out,
		const Engine3DRadSpace::Math::Quaternion& a,
		const Engine3DRadSpace::Math::Quaternion& b,
		float t
	);

	bool E3DRSP_SCRIPTING_EXPORT iQuaternionCompare2(
		const Engine3DRadSpace::Math::Quaternion& a,
		const Engine3DRadSpace::Math::Quaternion& b
	);

	bool E3DRSP_SCRIPTING_EXPORT iQuaternionCompare(
		const Engine3DRadSpace::Math::Quaternion& a,
		const Engine3DRadSpace::Math::Quaternion& b,
		float tolerance
	);

	int E3DRSP_SCRIPTING_EXPORT iFileReadOpen(const std::string& filename);
	int E3DRSP_SCRIPTING_EXPORT iFileWriteOpen(const std::string& filename);
	int E3DRSP_SCRIPTING_EXPORT iFileClose(int fileHandle);
	float E3DRSP_SCRIPTING_EXPORT iFileValueRead(int fileHandle);
	void E3DRSP_SCRIPTING_EXPORT iFileValueWrite(int fileHandle, float value, bool useNewline);
	int E3DRSP_SCRIPTING_EXPORT iFileByteRead(int fileHandle);
	void E3DRSP_SCRIPTING_EXPORT iFileByteWrite(int fileHandle, int value);
	void E3DRSP_SCRIPTING_EXPORT iFileStringRead(int fileHandle, std::string& out);
	void E3DRSP_SCRIPTING_EXPORT iFileStringWrite(int fileHandle, const std::string& value, bool useNewline);
	bool E3DRSP_SCRIPTING_EXPORT iFileEOF(int fileHandle);
	bool E3DRSP_SCRIPTING_EXPORT iFileExists(const std::string& filename);
	void E3DRSP_SCRIPTING_EXPORT iFileCopy(const std::string& source, const std::string& destination);
	void E3DRSP_SCRIPTING_EXPORT iFileDelete(const std::string& filename);
	void E3DRSP_SCRIPTING_EXPORT iFolderCreate(const std::string& folderName);
	void E3DRSP_SCRIPTING_EXPORT iFolderDelete(const std::string& folderName);
	int E3DRSP_SCRIPTING_EXPORT iFileDownload(const std::string& url, const std::string& destination);
	int E3DRSP_SCRIPTING_EXPORT iFileDownloadPB(const std::string& url, const std::string& destination);
	int E3DRSP_SCRIPTING_EXPORT iFileSize(const std::string& filename);
	void E3DRSP_SCRIPTING_EXPORT iLocalFolder(std::string& folderName);
	bool E3DRSP_SCRIPTING_EXPORT iFileOpenDialog(std::string& initialPath_outResult, const std::string& filter, std::string& title);
	bool E3DRSP_SCRIPTING_EXPORT iFileSaveDialog(std::string& initialPath_outResult, const std::string& filter, std::string& title);

	bool E3DRSP_SCRIPTING_EXPORT iKeyDown(int key);
	int E3DRSP_SCRIPTING_EXPORT iKeyCode(const std::string& keyName);
	int E3DRSP_SCRIPTING_EXPORT iTypedChar(bool);

	float E3DRSP_SCRIPTING_EXPORT iMouseX();
	float E3DRSP_SCRIPTING_EXPORT iMouseY();
	float E3DRSP_SCRIPTING_EXPORT iMouseZ();
	/*  mouse button codes can be 0=left, 1=right, 2=middle */
	bool E3DRSP_SCRIPTING_EXPORT iMouseButtonDown(int idBtn);
	bool E3DRSP_SCRIPTING_EXPORT iMouseButtonClick(int idBtn);
	//float E3DRSP_SCRIPTING_EXPORT iMouseLookX();
	//float E3DRSP_SCRIPTING_EXPORT iMouseLookY();
	//void E3DRSP_SCRIPTING_EXPORT iMouseLookSet(float x, float y);
	//iMouseLookSpeedSet(float,float)
	//iMouseLookYRangeSet(float,float)
	int E3DRSP_SCRIPTING_EXPORT iDLLLoad(const std::string& dllName);
	int E3DRSP_SCRIPTING_EXPORT iDLLUnload(int dllHandle);
	bool E3DRSP_SCRIPTING_EXPORT iDLLCall(int dllHandle, const std::string& functionName, int arg);
	void E3DRSP_SCRIPTING_EXPORT iDLLArraySet(int dllHandle, int index, float value);
	float E3DRSP_SCRIPTING_EXPORT iDLLArrayGet(int dllHandle, int index);

	bool E3DRSP_SCRIPTING_EXPORT iInitializing();
	bool E3DRSP_SCRIPTING_EXPORT iDeinitializing();
	void E3DRSP_SCRIPTING_EXPORT iScriptStop();
	int E3DRSP_SCRIPTING_EXPORT iObjectHandle(int);
	/// <summary>
	///    Return system clock data.
	/// For example, iSystemTime(4) will return current hour.
	/// </summary>
	/// <param name="identifier">Identifier of the information to return.
	/// 0 - Year
	/// 1 - Month
	/// 2 - DayOfWeek
	/// 3 - Day
	/// 4 - Hour
	/// 5 - Minute
	/// 6 - Second
	/// 7 - Milliseconds
	/// </param>
	/// <returns>The requested system time information.</returns>
	int E3DRSP_SCRIPTING_EXPORT iSystemTime(int identifier);
	int E3DRSP_SCRIPTING_EXPORT iDisplayWidth();
	int E3DRSP_SCRIPTING_EXPORT iDisplayHeight();
	bool E3DRSP_SCRIPTING_EXPORT iBoundingSphereFrustumCheckSet(bool enableCheck);
	int E3DRSP_SCRIPTING_EXPORT iVertexShaderVersion(bool minor);
	int E3DRSP_SCRIPTING_EXPORT iPixelShaderVersion(bool minor);
	void E3DRSP_SCRIPTING_EXPORT iRenderingEnable(bool enable);
	void E3DRSP_SCRIPTING_EXPORT iShadowsEnable(bool enable);
	void E3DRSP_SCRIPTING_EXPORT iEscKeyEnable();
	void E3DRSP_SCRIPTING_EXPORT iEscKeyDisable();
	//iSettingsDialogDisable()
	//iSettingsDialogEnable()
	// iSimulationQualitySet(int)
	//iSimulationFrqSet(float);
	bool E3DRSP_SCRIPTING_EXPORT iCommand(const std::string& command);
	bool E3DRSP_SCRIPTING_EXPORT iCommandContinue(const std::string& command);
	//void E3DRSP_SCRIPTING_EXPORT iExitDocumentSet(const std::string& document);
	bool E3DRSP_SCRIPTING_EXPORT i3DPointVisible(unsigned camera, const Engine3DRadSpace::Math::Vector3& point);
	bool E3DRSP_SCRIPTING_EXPORT iSphereVisible(unsigned camera, const Engine3DRadSpace::Math::Vector3& center, float radius);
	void E3DRSP_SCRIPTING_EXPORT i3DLocationToScreen(
		Engine3DRadSpace::Math::Vector3& outScreenLocation,
		const Engine3DRadSpace::Math::Vector3& location,
		unsigned camera
	);
	void E3DRSP_SCRIPTING_EXPORT iScreenRay(
		Engine3DRadSpace::Math::Vector3& outRayOrigin,
		Engine3DRadSpace::Math::Vector3& outRayDirection,
		const Engine3DRadSpace::Math::Vector3& screenLocation,
		unsigned camera
	);

	int E3DRSP_SCRIPTING_EXPORT iSphereSegmentIntersect(
		const Engine3DRadSpace::Math::Vector3& center,
		float radius,
		const Engine3DRadSpace::Math::Vector3& segStart,
		const Engine3DRadSpace::Math::Vector3& segEnd,
		Engine3DRadSpace::Math::Vector3& outIntersectionPoint,
		Engine3DRadSpace::Math::Vector3& outNormal
	);

	//bool E3DRSP_SCRIPTING_EXPORT iScreenAreaPicked(float topX, float topY, float bottomX, float bottomY, bool once);
	void E3DRSP_SCRIPTING_EXPORT iScreenshotSave(const std::string& filename);
	// iSuperScreenshotSave(string,int)
}