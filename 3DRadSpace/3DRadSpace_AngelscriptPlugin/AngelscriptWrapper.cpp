#include "AngelscriptWrapper.hpp"
//#define AS_USE_NAMESPACE

#include <cassert>
#include <format>

#include <Engine3DRadSpace\3DRadSpace.hpp>
#include "Legacy.hpp"

using namespace Engine3DRadSpace::Angelscript;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

//using namespace AngelScript;

void AngelScriptWrapper_MessageCallback(const asSMessageInfo* msg, void* param)
{
	if(msg->type == asMSGTYPE_WARNING)
		PrintWarning(std::format("({}, {}) : Warning {}", msg->section, msg->row, msg->col, msg->message));
	else if(msg->type == asMSGTYPE_INFORMATION)
		PrintMessage(std::format("({}, {}) : Information {}", msg->section, msg->row, msg->col, msg->message));
	if(msg->type == asMSGTYPE_ERROR)
		PrintWarning(std::format("({}, {}) : Error {}", msg->section, msg->row, msg->col, msg->message));
}

static void v2ctor_def(Vector2* self)
{
	new (self) Vector2;
}

static void v2ctor(float x, float y, Vector2* self)
{
	new (self) Vector2(x, y);
}

static void v2ctor_list(float* list, Vector2* self)
{
	new(self) Vector2(list[0], list[1]);
}

static void v2ctor_cpy(const Vector2& cpy, Vector2* self)
{
	new (self) Vector2(cpy);
}

static void v2dtor(Vector2* v)
{
	v->~Vector2();
}

static void v3ctor_def(Vector3* self)
{
	new (self) Vector3;
}

static void v3ctor(float x, float y, float z, Vector3* self)
{
	new (self) Vector3(x, y, z);
}

static void v3ctor_list(float* list, Vector3* self)
{
	new(self) Vector3(list[0], list[1], list[2]);
}

static void v3ctor_cpy(const Vector3& cpy, Vector3* self)
{
	new (self) Vector3(cpy);
}

static void v3dtor(Vector3* v)
{
	v->~Vector3();
}

static void v4ctor_def(Vector4* self)
{
	new (self) Vector4();
}

static void v4ctor(float x, float y, float z, float w, Vector4* self)
{
	new (self) Vector4(x, y, z, w);
}

static void v4ctor_list(float* list, Vector4* self)
{
	new (self) Vector4(list[0], list[1], list[2], list[3]);
}

static void v4ctor_cpy(const Vector4& copy, Vector4 *self)
{
	new (self) Vector4(copy);
}

static void v4dtor(Vector4* self)
{
	self->~Vector4();
}

static void q_ctor_def(Quaternion* self)
{
	new (self) Quaternion;
}

static void q_ctor(float x, float y, float z, float w, Quaternion* self)
{
	new (self) Quaternion(x, y, z, w);
}

static void q_ctor_list(float* list, Quaternion* self)
{
	new (self) Quaternion(list[0], list[1], list[2], list[3]);
}

static void q_ctor_cpy(const Quaternion& copy, Quaternion* self)
{
	new (self) Quaternion(copy);
}

AngelScriptWrapper::AngelScriptWrapper()
{
	// Create the script engine
	_engine = asCreateScriptEngine();
	if(_engine == nullptr)
		throw Exception("Failed to initialize AngelScript engine!");

	//https://www.angelcode.com/angelscript/sdk/docs/manual/doc_hello_world.html

	int r = _engine->SetMessageCallback(asFUNCTION(AngelScriptWrapper_MessageCallback), 0, asCALL_CDECL); assert( r >= 0 );
	RegisterStdString(_engine);

#pragma region Matrix3x3
	r = _engine->RegisterObjectType("Matrix3x3", sizeof(Matrix3x3), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
	// fields
	r = _engine->RegisterObjectProperty("Matrix3x3", "float M11", asOFFSET(Matrix3x3, M11)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix3x3", "float M12", asOFFSET(Matrix3x3, M12)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix3x3", "float M13", asOFFSET(Matrix3x3, M13)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix3x3", "float M21", asOFFSET(Matrix3x3, M21)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix3x3", "float M22", asOFFSET(Matrix3x3, M22)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix3x3", "float M23", asOFFSET(Matrix3x3, M23)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix3x3", "float M31", asOFFSET(Matrix3x3, M31)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix3x3", "float M32", asOFFSET(Matrix3x3, M32)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix3x3", "float M33", asOFFSET(Matrix3x3, M33)); assert(r >= 0);
#pragma endregion

#pragma region Matrix4x4
	r = _engine->RegisterObjectType("Matrix4x4", sizeof(Matrix4x4), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
	// fields
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M11", asOFFSET(Matrix4x4, M11)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M12", asOFFSET(Matrix4x4, M12)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M13", asOFFSET(Matrix4x4, M13)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M14", asOFFSET(Matrix4x4, M14)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M21", asOFFSET(Matrix4x4, M21)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M22", asOFFSET(Matrix4x4, M22)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M23", asOFFSET(Matrix4x4, M23)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M24", asOFFSET(Matrix4x4, M24)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M31", asOFFSET(Matrix4x4, M31)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M32", asOFFSET(Matrix4x4, M32)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M33", asOFFSET(Matrix4x4, M33)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M34", asOFFSET(Matrix4x4, M34)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M41", asOFFSET(Matrix4x4, M41)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M42", asOFFSET(Matrix4x4, M42)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M43", asOFFSET(Matrix4x4, M43)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Matrix4x4", "float M44", asOFFSET(Matrix4x4, M44)); assert(r >= 0);
#pragma endregion

#pragma region Vector2
	r = _engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

	//constructors
	r = _engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(v2ctor_def), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = _engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float x, float y)", asFUNCTION(v2ctor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = _engine->RegisterObjectBehaviour("Vector2", asBEHAVE_LIST_CONSTRUCT, "void f(int &in) {float, float}", asFUNCTION(v2ctor_list),  asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = _engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2& in)", asFUNCTION(v2ctor_cpy), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//destructor
	r = _engine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(v2dtor), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//fields
	r = _engine->RegisterObjectProperty("Vector2", "float X", asOFFSET(Vector2, X)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Vector2", "float Y", asOFFSET(Vector2, Y)); assert(r >= 0);

	//methods
	r = _engine->RegisterObjectMethod("Vector2", "float Length()", asMETHOD(Vector2, Length), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2", "float LengthSquared()", asMETHOD(Vector2, LengthSquared), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2", "float Angle()", asMETHOD(Vector2, Angle), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2", "float Dot(Vector2)", asMETHODPR(Vector2,Dot,(const Vector2&) const,float), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2", "Vector2& Normalize()", asMETHODPR(Vector2, Normalize, (), Vector2&), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2", "Vector2& RotateBy(float theta)", asMETHOD(Vector2, RotateBy), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2", "Vector2& Hadamard(const Vector2& in)", asMETHODPR(Vector2, Hadamard, (const Vector2&), Vector2&),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2", "Vector2& Transform(const Matrix3x3& in)", asMETHODPR(Vector2, Transform, (const Matrix3x3&), Vector2&),  asCALL_THISCALL); assert(r >= 0);

	//operators
	r = _engine->RegisterObjectMethod("Vector2","Vector2 opNeg()", asMETHODPR(Vector2, operator-,(),Vector2&),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2& opAddAssign(const Vector2& in)", asMETHOD(Vector2, operator+=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2& opSubAssign(const Vector2& in)", asMETHOD(Vector2, operator-=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2& opMulAssign(float)", asMETHOD(Vector2, operator*=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2& opDivAssign(float)", asMETHOD(Vector2, operator/=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2 opAdd(const Vector2& in)", asMETHOD(Vector2,operator+),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2 opSub(const Vector2& in)", asMETHODPR(Vector2,operator-,(const Vector2&) const,Vector2),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2 opMul(float)", asMETHODPR(Vector2,operator*,(float) const,Vector2),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2 opDiv(float)", asMETHOD(Vector2,operator/),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2 opMul_r(float)",asFUNCTIONPR(operator*,(float, const Vector2&),Vector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector2","Vector2 opDiv_r(float)",asFUNCTIONPR(operator/,(float, const Vector2&),Vector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
#pragma endregion

#pragma region Quaternion
	r = _engine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

	//constructors
	r = _engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(q_ctor_def), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = _engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(q_ctor), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = _engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_LIST_CONSTRUCT, "void f(int &in){float, float, float, float}", asFUNCTION(q_ctor_list), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = _engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion& in)", asFUNCTION(q_ctor_cpy), asCALL_CDECL_OBJLAST); assert(r >= 0);

	//fields
	r = _engine->RegisterObjectProperty("Quaternion", "float X", asOFFSET(Quaternion, X)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Quaternion", "float Y", asOFFSET(Quaternion, Y)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Quaternion", "float Z", asOFFSET(Quaternion, Z)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Quaternion", "float W", asOFFSET(Quaternion, W)); assert(r >= 0);

	//methods
	r = _engine->RegisterObjectMethod("Quaternion", "float Length()", asMETHOD(Quaternion, Length), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "float LengthSquared()", asMETHOD(Quaternion, LengthSquared), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "float Dot(const Quaternion& in)", asMETHODPR(Quaternion, Dot, (const Quaternion&) const, float), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion& Normalize()", asMETHODPR(Quaternion, Normalize, (), Quaternion&), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion& Hadamard(const Quaternion& in)", asMETHODPR(Quaternion, Hadamard, (const Quaternion&), Quaternion&), asCALL_THISCALL); assert(r >= 0);

	//operators
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion opNeg()", asMETHODPR(Quaternion, operator-, (), Quaternion&), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion& opAddAssign(const Quaternion& in)", asMETHOD(Quaternion, operator+=), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion& opSubAssign(const Quaternion& in)", asMETHOD(Quaternion, operator-=), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion& opMulAssign(float)", asMETHODPR(Quaternion, operator*=, (const Quaternion&), Quaternion&), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion& opDivAssign(float)", asMETHOD(Quaternion, operator/=), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion opAdd(const Quaternion& in)", asMETHOD(Quaternion, operator+), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion opSub(const Quaternion& in)", asMETHODPR(Quaternion, operator-, (const Quaternion&) const, Quaternion), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float)", asMETHODPR(Quaternion, operator*, (float) const, Quaternion), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion opDiv(float)", asMETHOD(Quaternion, operator/), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion opMul_r(float)", asFUNCTIONPR(operator*, (float, const Quaternion&), Quaternion), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Quaternion", "Quaternion opDiv_r(float)", asFUNCTIONPR(operator/, (float, const Quaternion&), Quaternion), asCALL_CDECL_OBJLAST); assert(r >= 0);
#pragma endregion

#pragma region Vector3
	r = _engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

	//constructors
	r = _engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(v3ctor_def), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = _engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float x, float y, float z)", asFUNCTION(v3ctor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = _engine->RegisterObjectBehaviour("Vector3", asBEHAVE_LIST_CONSTRUCT, "void f(int &in) {float, float, float}", asFUNCTION(v3ctor_list),  asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = _engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3& in)", asFUNCTION(v3ctor_list),  asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//destructor
	r = _engine->RegisterObjectBehaviour("Vector3", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(v3dtor), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//fields
	r = _engine->RegisterObjectProperty("Vector3", "float X", asOFFSET(Vector3, X)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Vector3", "float Y", asOFFSET(Vector3, Y)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Vector3", "float Z", asOFFSET(Vector3, Z)); assert(r >= 0);

	//methods
	r = _engine->RegisterObjectMethod("Vector3", "float Length()", asMETHOD(Vector3, Length), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3", "float LengthSquared()", asMETHOD(Vector3, LengthSquared), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3", "float Dot(const Vector3& in)", asMETHODPR(Vector3,Dot,(const Vector3&) const,float), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3", "Vector3& Cross(const Vector3& in)", asMETHODPR(Vector3,Cross,(const Vector3&) ,Vector3&), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3", "Vector3& Normalize()", asMETHODPR(Vector3, Normalize,(),Vector3&), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3", "Vector3& Hadamard(const Vector3& in)", asMETHODPR(Vector3, Hadamard, (const Vector3&), Vector3&),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3", "Vector3& Transform(const Matrix4x4& in)", asMETHODPR(Vector3, Transform, (const Matrix4x4&), Vector3&),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3", "Vector3& Transform(const Quaternion& in)", asMETHODPR(Vector3, Transform, (const Quaternion&), Vector3&),  asCALL_THISCALL); assert(r >= 0);

	//operators
	r = _engine->RegisterObjectMethod("Vector3","Vector3 opNeg()", asMETHODPR(Vector3, operator-,(),Vector3&),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3& opAddAssign(const Vector3& in)", asMETHOD(Vector3, operator+=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3& opSubAssign(const Vector3& in)", asMETHOD(Vector3, operator-=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3& opMulAssign(float)", asMETHOD(Vector3, operator*=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3& opDivAssign(float)", asMETHOD(Vector3, operator/=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3 opAdd(const Vector3& in)", asMETHOD(Vector3,operator+),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3 opSub(const Vector3& in)", asMETHODPR(Vector3,operator-,(const Vector3&) const,Vector3),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3 opMul(float)", asMETHODPR(Vector3,operator*,(float) const,Vector3),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3 opDiv(float)", asMETHOD(Vector3,operator/),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3 opMul_r(float)",asFUNCTIONPR(operator*,(float, const Vector3&),Vector3), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector3","Vector3 opDiv_r(float)",asFUNCTIONPR(operator/,(float, const Vector3&),Vector3), asCALL_CDECL_OBJLAST); assert(r >= 0);
#pragma endregion

#pragma region Vector4
	r = _engine->RegisterObjectType("Vector4", sizeof(Vector4), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

	//constructors
	r = _engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(v4ctor_def), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = _engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(v4ctor), asCALL_CDECL_OBJFIRST); assert(r >= 0);
	r = _engine->RegisterObjectBehaviour("Vector4", asBEHAVE_LIST_CONSTRUCT, "void f(int &in){float, float, float, float}", asFUNCTION(v4ctor_list), asCALL_CDECL_OBJFIRST); assert(r >= 0);
	r = _engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4& in)", asFUNCTION(v4ctor_cpy), asCALL_CDECL_OBJLAST); assert(r >= 0);

	//fields
	r = _engine->RegisterObjectProperty("Vector4", "float X", asOFFSET(Vector4, X)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Vector4", "float Y", asOFFSET(Vector4, Y)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Vector4", "float Z", asOFFSET(Vector4, Z)); assert(r >= 0);
	r = _engine->RegisterObjectProperty("Vector4", "float W", asOFFSET(Vector4, W)); assert(r >= 0);

	//methods
	r = _engine->RegisterObjectMethod("Vector4", "float Length()", asMETHOD(Vector4, Length), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4", "float LengthSquared()", asMETHOD(Vector4, LengthSquared), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4", "float Dot(const Vector4& in)", asMETHODPR(Vector4,Dot,(const Vector4&) const,float), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4", "Vector4& Normalize()", asMETHODPR(Vector4, Normalize,(),Vector4&), asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4", "Vector4& Hadamard(const Vector4& in)", asMETHODPR(Vector4, Hadamard, (const Vector4&), Vector4&),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4", "Vector4& Transform(const Matrix4x4& in)", asMETHODPR(Vector4, Transform, (const Matrix4x4&), Vector4&),  asCALL_THISCALL); assert(r >= 0);
	//r = _engine->RegisterObjectMethod("Vector4", "Vector3& Transform(const Quaternion&)", asMETHODPR(Vector4, Transform, (const Quaternion&), Vector3&),  asCALL_THISCALL); assert(r >= 0);

	//operators
	r = _engine->RegisterObjectMethod("Vector4","Vector4 opNeg()", asMETHODPR(Vector4, operator-,(),Vector4&),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4& opAddAssign(const Vector4& in)", asMETHOD(Vector4, operator+=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4& opSubAssign(const Vector4& in)", asMETHOD(Vector4, operator-=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4& opMulAssign(float)", asMETHOD(Vector4, operator*=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4& opDivAssign(float)", asMETHOD(Vector4, operator/=),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4 opAdd(const Vector4& in)", asMETHOD(Vector4,operator+),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4 opSub(const Vector4& in)", asMETHODPR(Vector4,operator-,(const Vector4&) const,Vector4),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4 opMul(float)", asMETHODPR(Vector4,operator*,(float) const,Vector4),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4 opDiv(float)", asMETHOD(Vector4,operator/),  asCALL_THISCALL); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4 opMul_r(float)",asFUNCTIONPR(operator*,(float, const Vector4&),Vector4), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = _engine->RegisterObjectMethod("Vector4","Vector4 opDiv_r(float)",asFUNCTIONPR(operator/,(float, const Vector4&),Vector4), asCALL_CDECL_OBJLAST); assert(r >= 0);
#pragma endregion

#pragma region Legacy
	//Register legacy functions similar to 3D Rad v7.22:
	r = _engine->RegisterGlobalFunction("void iObjectStart(const uint)", asFUNCTION(iObjectStart), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectStop(const uint)", asFUNCTION(iObjectStop), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectSwitch(const uint)", asFUNCTION(iObjectSwitch), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectShow(const uint)", asFUNCTION(iObjectShow), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectHide(const uint)", asFUNCTION(iObjectHide), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectShowHideSwitch(const uint)", asFUNCTION(iObjectShowHideSwitch), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectOrientation(const uint, Quaternion& in)", asFUNCTION(iObjectOrientation), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectOrientationSet(const uint, const Quaternion& in)", asFUNCTION(iObjectOrientationSet), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectOrientationReset(const uint, const Quaternion& in)", asFUNCTION(iObjectOrientationReset), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectLocation(const uint, Vector3& in)", asFUNCTION(iObjectLocation), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectLocationSet(const uint,const Vector3& in)", asFUNCTION(iObjectLocationSet), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectLocationReset(const uint,const Vector3& in)", asFUNCTION(iObjectLocationReset), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectPositionReset(const uint, const Quaternion& in, const Vector3& in)", asFUNCTION(iObjectPositionReset), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectScaleSet(const uint, const Vector3& in)", asFUNCTION(iObjectScaleSet), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectScale(const uint, Vector3& in)", asFUNCTION(iObjectScale), asCALL_CDECL); assert(r >= 0);
	// Physics functions
	r = _engine->RegisterGlobalFunction("float iObjectKmh(const uint)", asFUNCTION(iObjectKmh), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectVelocity(const uint, Vector3& in)", asFUNCTION(iObjectVelocity), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectVelocitySet(const uint, Vector3& in)", asFUNCTION(iObjectVelocitySet), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectSpin(const uint, Vector3& in)", asFUNCTION(iObjectSpin), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectSpinSet(const uint, Vector3& in)", asFUNCTION(iObjectSpinSet), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectTorqueApply(const uint, Vector3& in)", asFUNCTION(iObjectTorqueApply), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectAngularAccelerationApply(const uint, Vector3& in)", asFUNCTION(iObjectAngularAccelerationApply), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectForceApply(const uint, Vector3& in, Vector3& in)", asFUNCTION(iObjectForceApply), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectAccelerationApply(const uint, const Vector3& in)", asFUNCTION(iObjectAccelerationApply), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectDampingApply(const uint, Vector3& in, bool, bool)", asFUNCTION(iObjectDampingApply), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iObjectPicked(const uint, Vector3& in)", asFUNCTION(iObjectPicked), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iObjectScan(const uint, const Vector3& in, const Vector3& in, float, Vector3& in, Vector3& in)", asFUNCTION(iObjectScan), asCALL_CDECL); assert(r >= 0);
	// Object field manipulation functions
	r = _engine->RegisterGlobalFunction("void iObjectTextSet(const uint, const string& in)", asFUNCTION(iObjectTextSet), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectParamSet(const uint, int, float)", asFUNCTION(iObjectParamSet), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectRefresh(const uint, const string& in)", asFUNCTION(iObjectRefresh), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectReset(const uint)", asFUNCTION(iObjectReset), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iObjectChildTransform(const uint, const uint, const Vector3& in, const Vector3& in)", asFUNCTION(iObjectChildTransform), asCALL_CDECL); assert(r >= 0);
	// String functions
	r = _engine->RegisterGlobalFunction("int iStringLen(const string& in)", asFUNCTION(iStringLen), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iStringUCase(string& out, const string& in)", asFUNCTION(iStringUCase), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iStringLCase(string& out, const string& in)", asFUNCTION(iStringLCase), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iStringMid(string& out, const string& in, int, int)", asFUNCTION(iStringMid), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iStringLeft(string& out, const string& in, int)", asFUNCTION(iStringLeft), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iStringRight(string& out, const string& in, int)", asFUNCTION(iStringRight), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iStringFind(const string& in, const string& in, int)", asFUNCTION(iStringFind), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iStringReplace(string& out, const string& in, const string& in, const string& in)", asFUNCTION(iStringReplace), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iStringStr(string& out, const string& in)", asFUNCTION(iStringStr), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iStringVal(const string& in)", asFUNCTION(iStringVal), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iPrint(const string& in,float,float, uint)", asFUNCTION(iPrint), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iGlobalStringSet(const string& in, int)", asFUNCTION(iGlobalStringSet), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iGlobalStringGet(string& in, int)", asFUNCTION(iGlobalStringGet), asCALL_CDECL); assert(r >= 0);
	// Float functions
	r = _engine->RegisterGlobalFunction("float iFloatRand(float a, float b)", asFUNCTION(iFloatRand), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iFloatAbs(float)", asFUNCTION(iFloatAbs), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iFloatSin(float)", asFUNCTION(iFloatSin), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iFloatCos(float)", asFUNCTION(iFloatCos), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iFloatSqrt(float)", asFUNCTION(iFloatSqrt), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iFloatInterpolate(float, float, float, float, float, float)", asFUNCTION(iFloatInterpolate), asCALL_CDECL); assert(r >= 0);
	// Vector functions
	r = _engine->RegisterGlobalFunction("float iVectorLength(const Vector3& in)", asFUNCTION(iVectorLength), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iVectorLengthSq(const Vector3& in)", asFUNCTION(iVectorLengthSq), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iVectorLengthSet(Vector3& out, const Vector3& in, float)", asFUNCTION(iVectorLengthSq), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iVectorDot(const Vector3& in, const Vector3& in)", asFUNCTION(iVectorDot), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iVectorCross(Vector3& out, const Vector3& in, const Vector3& in)", asFUNCTION(iVectorCross), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iVectorRotate(Vector3& out, const Vector3& in, const Quaternion& in)", asFUNCTION(iVectorRotate), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iVectorEulerRotate(Vector3& out, const Vector3& in, float, float, float, string)", asFUNCTION(iVectorEulerRotate), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iVectorCompare(const Vector3& in, const Vector3& in, float)", asFUNCTION(iVectorCompare), asCALL_CDECL); assert(r >= 0);
	//Quaternion functions
	r = _engine->RegisterGlobalFunction("void iQuaternionFromAxisAngle(Quaternion& out, const Vector3& in)", asFUNCTION(iQuaternionFromAxisAngle), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iQuaternionFromEulerAngles(Quaternion& out, Vector3& in, float)", asFUNCTION(iQuaternionFromAxisAngle), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iQuaternionToEulerAngles(Vector3& out, const Quaternion& in)", asFUNCTION(iQuaternionToEulerAngles), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iQuaternionLookAt(Quaternion& out, const Vector3& in, const Vector3& in)", asFUNCTION(iQuaternionLookAt), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iQuaternionInterpolate(Quaternion& out, const Quaternion& in, const Quaternion& in, float)", asFUNCTION(iQuaternionInterpolate), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iQuaternionMultiply(Quaternion& out, const Quaternion& in, const Quaternion& in)", asFUNCTION(iQuaternionMultiply), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iQuaternionCompare(const Quaternion& in, const Quaternion& in)", asFUNCTION(iQuaternionCompare), asCALL_CDECL); assert(r >= 0);
	//File functions
	r = _engine->RegisterGlobalFunction("int iFileReadOpen(const string& in)", asFUNCTION(iFileReadOpen), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iFileWriteOpen(const string& in)", asFUNCTION(iFileWriteOpen), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iFileClose(int)", asFUNCTION(iFileClose), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iFileValueRead(int)", asFUNCTION(iFileValueRead), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iFileValueWrite(int, float)", asFUNCTION(iFileValueWrite), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iFileByteRead(int)", asFUNCTION(iFileByteRead), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iFileByteWrite(int, int)", asFUNCTION(iFileByteWrite), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iFileStringRead(int, string& out)", asFUNCTION(iFileStringRead), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iFileStringWrite(int, const string& in)", asFUNCTION(iFileStringWrite), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("bool iFileEOF(int)", asFUNCTION(iFileEOF), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("bool iFileExists(const string& in)", asFUNCTION(iFileExists), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iFileCopy(const string& in, const string& in)", asFUNCTION(iFileCopy), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iFileDelete(const string& in)", asFUNCTION(iFileDelete), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iFolderCreate(const string& in)", asFUNCTION(iFolderCreate), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iFolderDelete(const string& in)", asFUNCTION(iFolderDelete), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iFileSize(const string& in)", asFUNCTION(iFileSize), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iLocalFolder(const string& in)", asFUNCTION(iLocalFolder), asCALL_CDECL); assert(r >= 0);
	//Mouse functions
	r = _engine->RegisterGlobalFunction("float iMouseX(Vector2& out)", asFUNCTION(iMouseX), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iMouseY(Vector2& out)", asFUNCTION(iMouseY), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("float iMouseZ(Vector2& out)", asFUNCTION(iMouseZ), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("bool iMouseButtonDown(int)", asFUNCTION(iMouseButtonDown), asCALL_CDECL); assert(r >= 0);
	
	r = _engine->RegisterGlobalFunction("int iObjectHandle(int)", asFUNCTION(iObjectHandle), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iSystemTime(int)", asFUNCTION(iSystemTime), asCALL_CDECL); assert(r >= 0);
	//Graphics functions
	r = _engine->RegisterGlobalFunction("int iDisplayWidth()", asFUNCTION(iDisplayWidth), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("int iDisplayHeight()", asFUNCTION(iDisplayHeight), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iVertexShaderVersion(int)", asFUNCTION(iShaderVersion), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iPixelShaderVersion(int)", asFUNCTION(iShaderVersion), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iRenderingEnable(bool)", asFUNCTION(iRenderingEnable), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iEscKeyEnable()", asFUNCTION(iEscKeyEnable), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iEscKeyDisable()", asFUNCTION(iEscKeyDisable), asCALL_CDECL); assert(r >= 0);
	// OS functions
	r = _engine->RegisterGlobalFunction("void iCommand(const string& in)", asFUNCTION(iCommand), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iCommandContinue(const string& in)", asFUNCTION(iCommandContinue), asCALL_CDECL); assert(r >= 0);
	// Viewing frustum functions
	r = _engine->RegisterGlobalFunction("void i3DLocationToScreen(Vector3& out, uint, Vector4& out, const Vector3& in)", asFUNCTION(i3DLocationToScreen), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iScreenRay(Vector3& out, Vector3& out, const Vector3& in, uint)", asFUNCTION(iScreenRay), asCALL_CDECL); assert(r >= 0);
	// Uncategorized functions
	r = _engine->RegisterGlobalFunction("int iSphereSegmentIntersect(const Vector3& in, float, const Vector3& in, const Vector3& in, Vector3& out, Vector3& out)", asFUNCTION(iSphereSegmentIntersect), asCALL_CDECL); assert(r >= 0);
	r = _engine->RegisterGlobalFunction("void iScreenshotSave(const string& in)", asFUNCTION(iScreenshotSave), asCALL_CDECL); assert(r >= 0);
#pragma endregion

	_context = _engine->CreateContext();
}

void AngelScriptWrapper::Call(size_t scriptHandle, const std::string& name)
{
	_context->Prepare(_scriptModules[scriptHandle].MainFunction);
	_context->Execute();
}

void AngelScriptWrapper::Call(size_t scriptHandle, AngelScriptWrapper::FunctionID functionID)
{
	switch (functionID)
	{
	case FunctionID::Main:
		_context->Prepare(_scriptModules[scriptHandle].MainFunction);
		break;
	case FunctionID::Initialize:
		_context->Prepare(_scriptModules[scriptHandle].InitializeFunction);
		break;
	case FunctionID::Deinitialize:
		_context->Prepare(_scriptModules[scriptHandle].DeinitializeFunction);
		break;
	}
	_context->Execute();
}

constexpr const char* initializingVariables = 
"bool var3drsp_iInitializing = false;"
"bool iInitializing() { return var3drsp_iInitializing; }"
"bool iDeinitializing() { return !var3drsp_iInitializing; }"
"void Internal_E3DRSP_Initialize() { var3drsp_iInitializing = true; }"
"void Internal_E3DRSP_Deinitialize() { var3drsp_iInitializing = false; }";

int AngelScriptWrapper::Compile(const std::filesystem::path& scriptPath)
{
	std::ifstream file(scriptPath);
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	auto name = scriptPath.filename().string();

	auto module = _engine->GetModule(name.c_str(), asGM_ALWAYS_CREATE);
	module->AddScriptSection(name.c_str(), content.c_str(), content.size());
	module->AddScriptSection(name.c_str(), initializingVariables, strlen(initializingVariables));
	int r = module->Build();
	
	if (r >= 0)
	{
		_scriptModules.emplace_back(
			_scriptModules.size(),
			name,
			module,
			module->GetFunctionByName("main"),
			module->GetFunctionByName("Internal_E3DRSP_Initialize"),
			module->GetFunctionByName("Internal_E3DRSP_Deinitialize")
		);
	}

	return r;
}

AngelScriptWrapper::~AngelScriptWrapper()
{
	auto engine = static_cast<asIScriptEngine*>(_engine);
	engine->ShutDownAndRelease();
}

asIScriptEngine* AngelScriptWrapper::GetEngine() const noexcept 
{
	return _engine; 
}