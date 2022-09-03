#include "pch.h"
#include <IObjectReflection.hpp>

using namespace Engine3DRadSpace;

class TestObject : public IObject
{
public:
	int Value1;
	float Value2;
	Vector2 Value3;
	Vector4 Value4;
	ColorShader Value5;

	TestObject() : IObject(),Value1(0),Value2(0),Value3(0,0),Value4(0,0,0,0),Value5(0,0,0,1) {};

	Matrix GetTranslation() override
	{
		return Matrix::Matrix();
	}

	void Load() override
	{

	}

	void Update(float dt) override
	{
	}

	virtual void Draw(float dt, Game* g) override
	{
	}

	void Enable() override
	{
	}

	bool Validate() override
	{
		return true;
	}
};

__BEGIN_REFLECTOBJECT(TestObject)
	__REFLECTFIELD(TestObject, std::string, "Name", Name, "TestObject"),
	__REFLECTFIELD(TestObject, bool, "Enabled", Enabled, true),
	__REFLECTFIELD(TestObject, int, "Value 1", Value1, 123),
	__REFLECTFIELD(TestObject, float, "Value 2", Value2, 3.1415962f),
	__REFLECTFIELD(TestObject, Vector2, "Value 3", Value3, Vector2::One()),
	__REFLECTFIELD(TestObject, Vector3, "Position", Position, Vector3::Zero()),
	__REFLECTFIELD(TestObject, Quaternion, "Rotation", Rotation, Quaternion::Quaternion()),
	__REFLECTFIELD(TestObject, Vector4, "Value 4", Value4, Vector4::One()),
	__REFLECTFIELD(TestObject, ColorShader, "Value 5", Value5, ColorShader::ColorShader(1,0,0,1))
__END_REFLECTOBJECT(TestObject)

namespace ReflectionTests
{
	//Test(s) for Reflection::Reflect
	TEST(ReflectBeginMacroTest, ReflectionTest)
	{
		EXPECT_EQ(TestObjectReflInst.Size(), 9); //size test, we expect 9 exposed fields from "TestObject"
	}

	//Tests for ReflectedField/ReflectedFieldBase

	TEST(String_FieldTest, ReflectField)
	{
		//Check type
		EXPECT_EQ(TestObjectReflInst[0]->GetFieldType(), typeid(std::string));

		//Check visible name
		std::string str1(TestObjectReflInst[0]->GetVisibleName());
		EXPECT_EQ(str1, "Name");

		//Check default value
		std::string defval = "TestObject";
		std::string defval_from_refl = *(std::string*)TestObjectReflInst[0]->GetDefaultValue();
		EXPECT_EQ(defval_from_refl, defval);
	}
	TEST(Boolean_FieldTest, ReflectField)
	{
		EXPECT_EQ(TestObjectReflInst[1]->GetFieldType(), typeid(bool)); //type

		std::string str2(TestObjectReflInst[1]->GetVisibleName());
		EXPECT_EQ(str2, "Enabled"); //visible field name

		//check defualt value
		EXPECT_EQ(*(bool*)TestObjectReflInst[1]->GetDefaultValue(),true);
	}
	TEST(Integer_FieldTest, ReflectField)
	{
		EXPECT_EQ(TestObjectReflInst[2]->GetFieldType(), typeid(int)); //type

		std::string str3(TestObjectReflInst[2]->GetVisibleName());
		EXPECT_EQ(str3, "Value 1"); //check editor name

		EXPECT_EQ(*(int*)TestObjectReflInst[2]->GetDefaultValue(), 123); //check default value
	}
	TEST(Float_FieldTest, ReflectField)
	{
		EXPECT_EQ(TestObjectReflInst[3]->GetFieldType(), typeid(float));
		EXPECT_EQ(std::string(TestObjectReflInst[3]->GetVisibleName()),"Value 2"); //editor name
		EXPECT_FLOAT_EQ(*(float*)TestObjectReflInst[3]->GetDefaultValue(), 3.1415962f);
	}
	TEST(Vector2_FieldTest, ReflectField)
	{
		EXPECT_EQ(TestObjectReflInst[4]->GetFieldType(), typeid(Vector2)); //type
		
		std::string str5(TestObjectReflInst[4]->GetVisibleName()); 
		EXPECT_EQ(str5, "Value 3"); //name

		EXPECT_EQ(*(Vector2*)TestObjectReflInst[4]->GetDefaultValue(), Vector2::One()); //default value
	}
	TEST(Vector3_FieldTest, ReflectField)
	{
		EXPECT_EQ(TestObjectReflInst[5]->GetFieldType(), typeid(Vector3)); // type
		EXPECT_EQ(std::string(TestObjectReflInst[5]->GetVisibleName()), "Position"); //editor name
		EXPECT_EQ(*(Vector3*)TestObjectReflInst[5]->GetDefaultValue(), Vector3::Zero()); //default value
	}
	TEST(Quaternion_FieldTest, ReflectField)
	{
		EXPECT_EQ(TestObjectReflInst[6]->GetFieldType(), typeid(Quaternion)); //type
		EXPECT_EQ(std::string(TestObjectReflInst[6]->GetVisibleName()), "Rotation"); //editor name
		EXPECT_EQ(*(Quaternion*)TestObjectReflInst[6]->GetDefaultValue(), Quaternion::Quaternion()); //default value
	}
	TEST(Vector4_FieldTest, ReflectField)
	{
		EXPECT_EQ(TestObjectReflInst[7]->GetFieldType(), typeid(Vector4)); //type
		EXPECT_EQ(std::string(TestObjectReflInst[7]->GetVisibleName()), "Value 4"); //UI name
		EXPECT_EQ(*(Vector4*)TestObjectReflInst[7]->GetDefaultValue(), Vector4::One()); //default value
	}
	TEST(Color_FieldTest, ReflectField)
	{
		EXPECT_EQ(TestObjectReflInst[8]->GetFieldType(), typeid(ColorShader)); //type
		EXPECT_EQ(std::string(TestObjectReflInst[8]->GetVisibleName()), "Value 5"); //UI name
		EXPECT_EQ(*(ColorShader*)TestObjectReflInst[8]->GetDefaultValue(), ColorShader::ColorShader(1, 0, 0, 1)); //default value
	}



	TEST(TryWriteRead_StringField, ReflectFieldMem)
	{
		const std::string nstr = "Test Object newvalue";

		TestObject tobj;
		TestObjectReflInst[0]->TrySetF<std::string, TestObject>(&tobj, nstr);
		EXPECT_EQ(tobj.Name, nstr);

		std::string rstr = *TestObjectReflInst[0]->TryGetF<std::string, TestObject>(&tobj);

		EXPECT_EQ(rstr,nstr);
	}

	TEST(TryWriteRead_BooleanField, ReflectFieldMem)
	{
		TestObject tobj;
		TestObjectReflInst[1]->TrySetF<bool, TestObject>(&tobj, false);
		EXPECT_EQ(tobj.Enabled, false); //check if TrySetF() worked

		bool rbl = *TestObjectReflInst[1]->TryGetF<bool, TestObject>(&tobj);
		EXPECT_EQ(rbl, false); //check if TryGetF worked
	}

	TEST(TryWriteRead_IntegerField, ReflectFieldMem)
	{
		TestObject tobj;
		TestObjectReflInst[2]->TrySetF<int, TestObject>(&tobj, 12345);
		EXPECT_EQ(tobj.Value1, 12345);

		int ri = *TestObjectReflInst[2]->TryGetF<int, TestObject>(&tobj);
		EXPECT_EQ(ri, 12345);
	}

	TEST(TryWriteRead_Float, ReflectFieldMem)
	{
		TestObject tobj;
		TestObjectReflInst[3]->TrySetF<float, TestObject>(&tobj,(float) std::numbers::e);
		EXPECT_FLOAT_EQ(tobj.Value2, (float)std::numbers::e);

		float rf = *TestObjectReflInst[3]->TryGetF<float, TestObject>(&tobj);
		EXPECT_FLOAT_EQ(rf, (float)std::numbers::e);
	}

	TEST(TryWriteRead_Vector2, ReflectFieldMem)
	{
		TestObject tobj;
		Vector2 v{ (float)std::numbers::pi,(float)std::numbers::e };

		TestObjectReflInst[4]->TrySetF<Vector2, TestObject>(&tobj, v);
		EXPECT_EQ(tobj.Value3, v);

		Vector2 rv = *TestObjectReflInst[4]->TryGetF<Vector2, TestObject>(&tobj);
		EXPECT_EQ(rv, v);
	}

	TEST(TryWriteRead_Vector3, ReflectFieldMem)
	{
		TestObject tobj;
		Vector3 v{ (float)std::numbers::phi,(float)std::numbers::sqrt2,(float)std::numbers::sqrt3 };
		TestObjectReflInst[5]->TrySetF<Vector3, TestObject>(&tobj, v);
		EXPECT_EQ(tobj.Position, v);

		Vector3 rv = *TestObjectReflInst[5]->TryGetF<Vector3, TestObject>(&tobj);
		EXPECT_EQ(rv, v);
	}

	TEST(TryWriteRead_Quaternion, ReflectFieldMem)
	{
		TestObject tobj;
		Quaternion q = Quaternion::CreateFromYawPitchRoll((float)std::numbers::pi / 2, 0, 0);
		TestObjectReflInst[6]->TrySetF<Quaternion, TestObject>(&tobj, q);
		EXPECT_EQ(tobj.Rotation, q);

		Quaternion rq = *TestObjectReflInst[6]->TryGetF<Quaternion, TestObject>(&tobj);
		EXPECT_EQ(rq, q);
	}

	TEST(TryWriteRead_Vector4, ReflectFieldMem)
	{
		TestObject tobj;
		Vector4 v{ (float)std::numbers::inv_sqrtpi,(float)std::numbers::ln10,(float)std::numbers::log10e,(float)std::numbers::log2e };
		TestObjectReflInst[7]->TrySetF<Vector4, TestObject>(&tobj, v);
		EXPECT_EQ(tobj.Value4, v);

		Vector4 rv = *TestObjectReflInst[7]->TryGetF<Vector4, TestObject>(&tobj);
		EXPECT_EQ(rv, v);
	}

	TEST(TryWriteRead_ShaderColor, ReflectFieldMem)
	{
		TestObject tobj;
		ColorShader yellow{ 1,1,0,1 };
		TestObjectReflInst[8]->TrySetF<ColorShader, TestObject>(&tobj, yellow);
		EXPECT_EQ(tobj.Value5, yellow);

		ColorShader rc = *TestObjectReflInst[8]->TryGetF<ColorShader, TestObject>(&tobj);
		EXPECT_EQ(rc, yellow);
	}
	
	TEST(EndReflectObject, ReflectObject)
	{
		EXPECT_EQ(&TestObjectReflInst, &(TestObjectGetRefl())); //check if TestObjectGetRefl() works properly
	}
	
}