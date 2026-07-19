#include "pch.h"
#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/Objects/IObject3D.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Content;

class TestObject : public IObject3D
{
public:
	TestObject() : IObject3D("Test object"), 
		Integer(5),
		Float(1.0f), 
		TestKey(Key::Space),
		OptValue(33)
	{
	}

	std::optional<int> OptValue;

	// Inherited via IObject
	void Initialize() override
	{
	}

	void Load() override
	{
	}

	void Load(const std::filesystem::path &dummy) override
	{
	}

	void Update() override
	{
	}

	void Draw3D() override
	{
	}

	Objects::Gizmos::IGizmo* GetGizmo() const noexcept override
	{
		return nullptr;
	}

	Reflection::UUID GetUUID() const noexcept override
	{
	// {017161C9-9EB7-4C10-AEEE-24347466586D}
	return {0x17161c9, 0x9eb7, 0x4c10, { 0xae, 0xee, 0x24, 0x34, 0x74, 0x66, 0x58, 0x6d }};
}

float Intersects(const Ray &r) override
{
	return std::numeric_limits<float>::signaling_NaN();
}

int MyMethod(int a, int b)
	{
		return a + b + Integer;
	}

	void Method()
	{
		Integer = -1;
	}

	int Integer;
	float Float;
	Color Colour;
	Math::Rectangle Rectangle1;
	RectangleF Rectangle2;

	Vector4 Vector;
	Key TestKey;
};

static int MyFunction(int a, int b)
{
	return a + b;
}

REFL_BEGIN(TestObject, "Test Object", "Tests", "Dummy test object")
	REFL_FIELD(TestObject, std::string, Name, "Name", "Test object", "Name of the object")
	REFL_FIELD(TestObject, bool, Enabled, "Enabled", true, "Is the object enabled?")
	REFL_FIELD(TestObject, bool, Visible, "Visible", true, "Is the object visible?")
	REFL_FIELD(TestObject, Vector3, Position, "Position", Vector3::Zero(), "Object position in world")
	REFL_FIELD(TestObject, Vector3, RotationCenter, "Rotation center", Vector3::Zero(), "Rotation pivot point")
	REFL_FIELD(TestObject, Quaternion, Rotation, "Rotation", Quaternion(), "Rotation")
	REFL_FIELD(TestObject, Vector3, Scale, "Scale", Vector3::One(), "Object scale")
	REFL_FIELD(TestObject, int, Integer, "Test Integer", 5, "int32_t value used for testing")
	REFL_FIELD(TestObject, float, Float, "Test float", 1.0f, "test float value")
	REFL_FIELD(TestObject, Color, Colour, "Test color", Colors::White, "test color")
	REFL_FIELD(TestObject, Math::Rectangle, Rectangle1, "Test rectangle 1", Math::Rectangle(1, 2, 3, 4), "integer rectangle")
	REFL_FIELD(TestObject, RectangleF, Rectangle2, "Test rectangle 2", RectangleF(5, 4, 3, 2), "float rectangle")
	REFL_FIELD(TestObject, Vector4, Vector, "Vector4", Vector4(0, 0, 0, 1), "Test vector4")
	REFL_FIELD(TestObject, Key, TestKey, "Test key", Key::ESC, "Dummy test key")
	REFL_FIELD(TestObject, std::optional<int>, OptValue, "Optional int", 55, "Optional test")
	REFL_METHOD(TestObject, int, &TestObject::MyMethod, "Test method", int, int)
	REFL_METHOD(TestObject, void, &TestObject::Method, "Method")
	REFL_FUNCTION(int, MyFunction, "Test function", int, int)
REFL_END

TEST(ReflectionTests, VisibleStrings)
{
	EXPECT_EQ(TestObjectReflInstance[0]->FieldName(), std::string("Name")); //visible name
	EXPECT_EQ(TestObjectReflInstance[0]->FieldDesc(), std::string("Name of the object")); //description
	
	//default value
	std::string v = *static_cast<const std::string*>(TestObjectReflInstance[0]->DefaultValue());
	EXPECT_EQ(v, "Test object");
}

TEST(ReflectionTests, SizeTests)
{
	EXPECT_EQ(TestObjectReflInstance[0]->TypeSize(), sizeof(std::string)); //test sizeof(T)
	EXPECT_EQ(TestObjectReflInstance[0]->TypeHash(), typeid(std::string).hash_code()); //object hash code
	EXPECT_EQ(TestObjectReflInstance["Test float"]->FieldOffset(), offsetof(TestObject, Float)); //test the offset.
}

#define TestFieldRW(id, fieldName, type, value) \
TEST(ReflectionTests, fieldName##RW ) \
{ \
	TestObject test; \
	type temp = value; \
	TestObjectReflInstance[id]->Set(&test, &temp); \
	EXPECT_EQ(temp, test. fieldName); \
	EXPECT_EQ(*static_cast<const type *>(TestObjectReflInstance[id]->Get(&test)), temp); \
}

TestFieldRW(0, Name, std::string, "Test name")
TestFieldRW(1, Enabled, bool, true)
TestFieldRW(2, Visible, bool, true)
TestFieldRW(3, Position, Vector3, Vector3(1,2,3))
TestFieldRW(4, RotationCenter, Vector3, Vector3(5,5,5))
TestFieldRW(5, Rotation, Quaternion, Quaternion(1,2,3,4))
TestFieldRW(6, Scale, Vector3, Vector3(3,3,3))
TestFieldRW(7, Integer, int, 34)
TestFieldRW(8, Float, float, 3.141f)
TestFieldRW(9, Colour, Color, Colors::Red)
TestFieldRW(10, Rectangle1, Math::Rectangle, Math::Rectangle(1,2,3,4))
TestFieldRW(11, Rectangle2, Math::RectangleF, Math::RectangleF(1.1f ,2.2f ,3.3f ,4.4f))
TestFieldRW(12, Vector, Vector4, Vector4(4,3,2,1))
TestFieldRW(13, TestKey, Key, Key::Enter)

TEST(ReflectionTests, UUIDTest)
{
	TestObject o;
	TestObjectReflInstance.ObjectUUID == o.GetUUID();
}

TEST(ReflectionTests, MethodTest_AnyOverload)
{
	TestObject o;

	auto method = static_cast<const IReflectedFunction*>(TestObjectReflInstance["Test method"]);
	std::array<Any, 2> args = { Any(1), Any(3) };

	Any n = method->Invoke(static_cast<void*>(&o), args);

	EXPECT_EQ(n.Get<int>(), 9); //1 + 3 + 5 = 9
}

//TEST(ReflectionTests, MethodTest_VoidOverload)
//{
//	TestObject o;
//
//	auto method = static_cast<const IReflectedFunction*>(TestObjectReflInstance["Test method"]);
//
//	int a = 20;
//	int b = 70;
//	int r = 0;
//
//	std::array<void*,2> args = { static_cast<void*>(&a), static_cast<void*>(&b) };
//
//	//method->Invoke(&r,static_cast<void*>(&o), args);
//
//	EXPECT_EQ(r, 95); //20 + 70 + 5 = 95
//}

TEST(ReflectionTests, FunctionTest_AnyOverload)
{
	auto method = static_cast<const IReflectedFunction*>(TestObjectReflInstance["Test function"]);
	std::array<Any, 2> args = { Any(6), Any(8) };
	Any n = method->Invoke(nullptr, args);
	EXPECT_EQ(n.Get<int>(), 14); //6 + 8 = 14
}

//TEST(ReflectionTests, FunctionTest_VoidOverload)
//{
//	auto method = static_cast<const IReflectedFunction*>(TestObjectReflInstance["Test function"]);
//
//	int a = 56;
//	int b = 44;
//	int r = 0;
//
//	std::array<void*, 2> args = { static_cast<void*>(&a), static_cast<void*>(&b) };
//	method->Invoke(&r, nullptr, args);
//	EXPECT_EQ(r, 100); //56 + 44 = 100
//}

TEST(ReflectionTests, FunctionTests_StateChange)
{
	TestObject o;

	auto method = static_cast<const IReflectedFunction*>(TestObjectReflInstance["Method"]);
	std::ignore = method->Invoke(&o, {});

	EXPECT_EQ(o.Integer, -1); //Integer should be -1
}