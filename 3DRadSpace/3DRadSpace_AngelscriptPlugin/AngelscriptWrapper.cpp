#include "AngelscriptWrapper.hpp"

//#define AS_USE_NAMESPACE
#include <angelscript.h>
#include "AngelScript_AddOns\scriptstdstring.h"

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

	auto engine = static_cast<asIScriptEngine*>(_engine);

	int r = engine->SetMessageCallback(asFUNCTION(AngelScriptWrapper_MessageCallback), 0, asCALL_CDECL); assert( r >= 0 );
	RegisterStdString(engine);

#pragma region Matrix3x3
	r = engine->RegisterObjectType("Matrix3x3", sizeof(Matrix3x3), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
#pragma endregion

#pragma region Matrix4x4
	r = engine->RegisterObjectType("Matrix4x4", sizeof(Matrix3x3), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
#pragma endregion

#pragma region Vector2
	r = engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

	//constructors
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(v2ctor_def), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float x, float y)", asFUNCTION(v2ctor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_LIST_CONSTRUCT, "void f(int &in) {float, float}", asFUNCTION(v2ctor_list),  asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2& in)", asFUNCTION(v2ctor_cpy), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//destructor
	r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(v2dtor), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//fields
	r = engine->RegisterObjectProperty("Vector2", "float X", asOFFSET(Vector2, X)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Vector2", "float Y", asOFFSET(Vector2, Y)); assert(r >= 0);

	//methods
	r = engine->RegisterObjectMethod("Vector2", "float Length()", asMETHOD(Vector2, Length), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "float LengthSquared()", asMETHOD(Vector2, LengthSquared), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "float Angle()", asMETHOD(Vector2, Angle), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "float Dot(Vector2)", asMETHODPR(Vector2,Dot,(const Vector2&) const,float), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "Vector2& Normalize()", asMETHODPR(Vector2, Normalize, (), Vector2&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "Vector2& RotateBy(float theta)", asMETHOD(Vector2, RotateBy), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "Vector2& Hadamard(const Vector2& in)", asMETHODPR(Vector2, Hadamard, (const Vector2&), Vector2&),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2", "Vector2& Transform(const Matrix3x3& in)", asMETHODPR(Vector2, Transform, (const Matrix3x3&), Vector2&),  asCALL_THISCALL); assert(r >= 0);

	//operators
	r = engine->RegisterObjectMethod("Vector2","Vector2 opNeg()", asMETHODPR(Vector2, operator-,(),Vector2&),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2& opAddAssign(const Vector2& in)", asMETHOD(Vector2, operator+=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2& opSubAssign(const Vector2& in)", asMETHOD(Vector2, operator-=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2& opMulAssign(float)", asMETHOD(Vector2, operator*=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2& opDivAssign(float)", asMETHOD(Vector2, operator/=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opAdd(const Vector2& in)", asMETHOD(Vector2,operator+),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opSub(const Vector2& in)", asMETHODPR(Vector2,operator-,(const Vector2&) const,Vector2),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opMul(float)", asMETHODPR(Vector2,operator*,(float) const,Vector2),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opDiv(float)", asMETHOD(Vector2,operator/),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opMul_r(float)",asFUNCTIONPR(operator*,(float, const Vector2&),Vector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector2","Vector2 opDiv_r(float)",asFUNCTIONPR(operator/,(float, const Vector2&),Vector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
#pragma endregion

#pragma region Quaternion
	r = engine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

	//constructors
	r = engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(q_ctor_def), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(q_ctor), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_LIST_CONSTRUCT, "void f(int &in){float, float, float, float}", asFUNCTION(q_ctor_list), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion& in)", asFUNCTION(q_ctor_cpy), asCALL_CDECL_OBJLAST); assert(r >= 0);

	//fields
	r = engine->RegisterObjectProperty("Quaternion", "float X", asOFFSET(Quaternion, X)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Quaternion", "float Y", asOFFSET(Quaternion, Y)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Quaternion", "float Z", asOFFSET(Quaternion, Z)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Quaternion", "float W", asOFFSET(Quaternion, W)); assert(r >= 0);

	//methods
	r = engine->RegisterObjectMethod("Quaternion", "float Length()", asMETHOD(Quaternion, Length), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "float LengthSquared()", asMETHOD(Quaternion, LengthSquared), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "float Dot(const Quaternion& in)", asMETHODPR(Quaternion, Dot, (const Quaternion&) const, float), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion& Normalize()", asMETHODPR(Quaternion, Normalize, (), Quaternion&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion& Hadamard(const Quaternion& in)", asMETHODPR(Quaternion, Hadamard, (const Quaternion&), Quaternion&), asCALL_THISCALL); assert(r >= 0);

	//operators
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion opNeg()", asMETHODPR(Quaternion, operator-, (), Quaternion&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion& opAddAssign(const Quaternion& in)", asMETHOD(Quaternion, operator+=), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion& opSubAssign(const Quaternion& in)", asMETHOD(Quaternion, operator-=), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion& opMulAssign(float)", asMETHODPR(Quaternion, operator*=, (const Quaternion&), Quaternion&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion& opDivAssign(float)", asMETHOD(Quaternion, operator/=), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion opAdd(const Quaternion& in)", asMETHOD(Quaternion, operator+), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion opSub(const Quaternion& in)", asMETHODPR(Quaternion, operator-, (const Quaternion&) const, Quaternion), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float)", asMETHODPR(Quaternion, operator*, (float) const, Quaternion), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion opDiv(float)", asMETHOD(Quaternion, operator/), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion opMul_r(float)", asFUNCTIONPR(operator*, (float, const Quaternion&), Quaternion), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Quaternion", "Quaternion opDiv_r(float)", asFUNCTIONPR(operator/, (float, const Quaternion&), Quaternion), asCALL_CDECL_OBJLAST); assert(r >= 0);
#pragma endregion

#pragma region Vector3
	r = engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

	//constructors
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(v3ctor_def), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float x, float y, float z)", asFUNCTION(v3ctor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_LIST_CONSTRUCT, "void f(int &in) {float, float, float}", asFUNCTION(v3ctor_list),  asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3& in)", asFUNCTION(v3ctor_list),  asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//destructor
	r = engine->RegisterObjectBehaviour("Vector3", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(v3dtor), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	//fields
	r = engine->RegisterObjectProperty("Vector3", "float X", asOFFSET(Vector3, X)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Vector3", "float Y", asOFFSET(Vector3, Y)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Vector3", "float Z", asOFFSET(Vector3, Z)); assert(r >= 0);

	//methods
	r = engine->RegisterObjectMethod("Vector3", "float Length()", asMETHOD(Vector3, Length), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3", "float LengthSquared()", asMETHOD(Vector3, LengthSquared), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3", "float Dot(const Vector3& in)", asMETHODPR(Vector3,Dot,(const Vector3&) const,float), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3", "Vector3& Cross(const Vector3& in)", asMETHODPR(Vector3,Cross,(const Vector3&) ,Vector3&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3", "Vector3& Normalize()", asMETHODPR(Vector3, Normalize,(),Vector3&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3", "Vector3& Hadamard(const Vector3& in)", asMETHODPR(Vector3, Hadamard, (const Vector3&), Vector3&),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3", "Vector3& Transform(const Matrix4x4& in)", asMETHODPR(Vector3, Transform, (const Matrix4x4&), Vector3&),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3", "Vector3& Transform(const Quaternion& in)", asMETHODPR(Vector3, Transform, (const Quaternion&), Vector3&),  asCALL_THISCALL); assert(r >= 0);

	//operators
	r = engine->RegisterObjectMethod("Vector3","Vector3 opNeg()", asMETHODPR(Vector3, operator-,(),Vector3&),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3& opAddAssign(const Vector3& in)", asMETHOD(Vector3, operator+=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3& opSubAssign(const Vector3& in)", asMETHOD(Vector3, operator-=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3& opMulAssign(float)", asMETHOD(Vector3, operator*=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3& opDivAssign(float)", asMETHOD(Vector3, operator/=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3 opAdd(const Vector3& in)", asMETHOD(Vector3,operator+),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3 opSub(const Vector3& in)", asMETHODPR(Vector3,operator-,(const Vector3&) const,Vector3),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3 opMul(float)", asMETHODPR(Vector3,operator*,(float) const,Vector3),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3 opDiv(float)", asMETHOD(Vector3,operator/),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3 opMul_r(float)",asFUNCTIONPR(operator*,(float, const Vector3&),Vector3), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector3","Vector3 opDiv_r(float)",asFUNCTIONPR(operator/,(float, const Vector3&),Vector3), asCALL_CDECL_OBJLAST); assert(r >= 0);
#pragma endregion

#pragma region Vector4
	r = engine->RegisterObjectType("Vector4", sizeof(Vector4), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);

	//constructors
	r = engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(v4ctor_def), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(v4ctor), asCALL_CDECL_OBJFIRST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Vector4", asBEHAVE_LIST_CONSTRUCT, "void f(int &in){float, float, float, float}", asFUNCTION(v4ctor_list), asCALL_CDECL_OBJFIRST); assert(r >= 0);
	r = engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4& in)", asFUNCTION(v4ctor_cpy), asCALL_CDECL_OBJLAST); assert(r >= 0);

	//fields
	r = engine->RegisterObjectProperty("Vector4", "float X", asOFFSET(Vector4, X)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Vector4", "float Y", asOFFSET(Vector4, Y)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Vector4", "float Z", asOFFSET(Vector4, Z)); assert(r >= 0);
	r = engine->RegisterObjectProperty("Vector4", "float W", asOFFSET(Vector4, W)); assert(r >= 0);

	//methods
	r = engine->RegisterObjectMethod("Vector4", "float Length()", asMETHOD(Vector4, Length), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4", "float LengthSquared()", asMETHOD(Vector4, LengthSquared), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4", "float Dot(const Vector4& in)", asMETHODPR(Vector4,Dot,(const Vector4&) const,float), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4", "Vector4& Normalize()", asMETHODPR(Vector4, Normalize,(),Vector4&), asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4", "Vector4& Hadamard(const Vector4& in)", asMETHODPR(Vector4, Hadamard, (const Vector4&), Vector4&),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4", "Vector4& Transform(const Matrix4x4& in)", asMETHODPR(Vector4, Transform, (const Matrix4x4&), Vector4&),  asCALL_THISCALL); assert(r >= 0);
	//r = engine->RegisterObjectMethod("Vector4", "Vector3& Transform(const Quaternion&)", asMETHODPR(Vector4, Transform, (const Quaternion&), Vector3&),  asCALL_THISCALL); assert(r >= 0);

	//operators
	r = engine->RegisterObjectMethod("Vector4","Vector4 opNeg()", asMETHODPR(Vector4, operator-,(),Vector4&),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4& opAddAssign(const Vector4& in)", asMETHOD(Vector4, operator+=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4& opSubAssign(const Vector4& in)", asMETHOD(Vector4, operator-=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4& opMulAssign(float)", asMETHOD(Vector4, operator*=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4& opDivAssign(float)", asMETHOD(Vector4, operator/=),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4 opAdd(const Vector4& in)", asMETHOD(Vector4,operator+),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4 opSub(const Vector4& in)", asMETHODPR(Vector4,operator-,(const Vector4&) const,Vector4),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4 opMul(float)", asMETHODPR(Vector4,operator*,(float) const,Vector4),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4 opDiv(float)", asMETHOD(Vector4,operator/),  asCALL_THISCALL); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4 opMul_r(float)",asFUNCTIONPR(operator*,(float, const Vector4&),Vector4), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = engine->RegisterObjectMethod("Vector4","Vector4 opDiv_r(float)",asFUNCTIONPR(operator/,(float, const Vector4&),Vector4), asCALL_CDECL_OBJLAST); assert(r >= 0);
#pragma endregion

#pragma region Legacy
	//Register legacy functions similar to 3D Rad v7.22:
	r = engine->RegisterGlobalFunction("void iObjectStart(const uint)", asFUNCTION(iObjectStart), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectStop(const uint)", asFUNCTION(iObjectStop), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectSwitch(const uint)", asFUNCTION(iObjectSwitch), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectShow(const uint)", asFUNCTION(iObjectShow), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectHide(const uint)", asFUNCTION(iObjectHide), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectShowHideSwitch(const uint)", asFUNCTION(iObjectShowHideSwitch), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectOrientation(const uint, Quaternion& in)", asFUNCTION(iObjectOrientation), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectOrientationSet(const uint, const Quaternion& in)", asFUNCTION(iObjectOrientationSet), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectLocation(const uint, Vector3& in)", asFUNCTION(iObjectLocation), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectLocationSet(const uint,const Vector3& in)", asFUNCTION(iObjectLocationSet), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectScaleSet(const uint, const Vector3& in)", asFUNCTION(iObjectScaleSet), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void iObjectScale(const uint, Vector3& in)", asFUNCTION(iObjectScale), asCALL_CDECL); assert(r >= 0);
#pragma endregion
}

void AngelScriptWrapper::Call(const std::string& name)
{
	auto engine = static_cast<asIScriptEngine*>(_engine);
}

AngelScriptWrapper::~AngelScriptWrapper()
{
	auto engine = static_cast<asIScriptEngine*>(_engine);
	engine->ShutDownAndRelease();
}
