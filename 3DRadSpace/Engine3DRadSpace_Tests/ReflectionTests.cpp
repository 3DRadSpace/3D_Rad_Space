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
	std::vector<int> IntVector;
	std::vector<float> FloatVector;
	std::vector<Vector3> VectorVector;

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

	float Intersects(const Ray &r) const override
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
	REFL_FIELD_VEC(TestObject, int, IntVector, "IntVector", "Vector of integers", {1, 2, 3})
	REFL_FIELD_VEC(TestObject, float, FloatVector, "FloatVector", "Vector of floats", {1.1f, 2.2f, 3.3f})
	REFL_FIELD_VEC(TestObject, Vector3, VectorVector, "VectorVector", "Vector of Vector3", {})
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

// Tests for std::vector<T> specialization using reflection

TEST(ReflectionTests, VectorIntReflectionDefaultValue)
{
	// Test that vector fields have correct default values through reflection
	const auto* field = TestObjectReflInstance["IntVector"];
	EXPECT_NE(field, nullptr);

	const std::vector<int>* defVal = static_cast<const std::vector<int>*>(field->DefaultValue());
	EXPECT_EQ(defVal->size(), 3);
	EXPECT_EQ((*defVal)[0], 1);
	EXPECT_EQ((*defVal)[1], 2);
	EXPECT_EQ((*defVal)[2], 3);
}

TEST(ReflectionTests, VectorFloatReflectionDefaultValue)
{
	// Test that float vector fields have correct default values through reflection
	const auto* field = TestObjectReflInstance["FloatVector"];
	EXPECT_NE(field, nullptr);

	const std::vector<float>* defVal = static_cast<const std::vector<float>*>(field->DefaultValue());
	EXPECT_EQ(defVal->size(), 3);
	EXPECT_FLOAT_EQ((*defVal)[0], 1.1f);
	EXPECT_FLOAT_EQ((*defVal)[1], 2.2f);
	EXPECT_FLOAT_EQ((*defVal)[2], 3.3f);
}

TEST(ReflectionTests, VectorIntReflectionWrite)
{
	// Test writing to a vector field through reflection
	TestObject test;
	const auto* field = TestObjectReflInstance["IntVector"];

	std::vector<int> newVec = {10, 20, 30, 40};
	field->Set(&test, &newVec);

	EXPECT_EQ(test.IntVector.size(), 4);
	EXPECT_EQ(test.IntVector[0], 10);
	EXPECT_EQ(test.IntVector[1], 20);
	EXPECT_EQ(test.IntVector[2], 30);
	EXPECT_EQ(test.IntVector[3], 40);
}

TEST(ReflectionTests, VectorFloatReflectionWrite)
{
	// Test writing to a float vector field through reflection
	TestObject test;
	const auto* field = TestObjectReflInstance["FloatVector"];

	std::vector<float> newVec = {5.5f, 6.6f, 7.7f};
	field->Set(&test, &newVec);

	EXPECT_EQ(test.FloatVector.size(), 3);
	EXPECT_FLOAT_EQ(test.FloatVector[0], 5.5f);
	EXPECT_FLOAT_EQ(test.FloatVector[1], 6.6f);
	EXPECT_FLOAT_EQ(test.FloatVector[2], 7.7f);
}

TEST(ReflectionTests, VectorIntReflectionRead)
{
	// Test reading from a vector field through reflection
	TestObject test;
	test.IntVector = {100, 200, 300};
	const auto* field = TestObjectReflInstance["IntVector"];

	const void* ptr = field->Get(&test);
	const std::vector<int>* readVec = static_cast<const std::vector<int>*>(ptr);

	EXPECT_EQ(readVec->size(), 3);
	EXPECT_EQ((*readVec)[0], 100);
	EXPECT_EQ((*readVec)[1], 200);
	EXPECT_EQ((*readVec)[2], 300);
}

TEST(ReflectionTests, VectorFloatReflectionRead)
{
	// Test reading from a float vector field through reflection
	TestObject test;
	test.FloatVector = {11.1f, 22.2f, 33.3f, 44.4f};
	const auto* field = TestObjectReflInstance["FloatVector"];

	const void* ptr = field->Get(&test);
	const std::vector<float>* readVec = static_cast<const std::vector<float>*>(ptr);

	EXPECT_EQ(readVec->size(), 4);
	EXPECT_FLOAT_EQ((*readVec)[0], 11.1f);
	EXPECT_FLOAT_EQ((*readVec)[1], 22.2f);
	EXPECT_FLOAT_EQ((*readVec)[2], 33.3f);
	EXPECT_FLOAT_EQ((*readVec)[3], 44.4f);
}

TEST(ReflectionTests, VectorIntReflectionOffset)
{
	// Test that vector fields report correct offset through reflection
	const auto* field = TestObjectReflInstance["IntVector"];
	EXPECT_EQ(field->FieldOffset(), offsetof(TestObject, IntVector));
}

TEST(ReflectionTests, VectorFloatReflectionOffset)
{
	// Test that float vector fields report correct offset through reflection
	const auto* field = TestObjectReflInstance["FloatVector"];
	EXPECT_EQ(field->FieldOffset(), offsetof(TestObject, FloatVector));
}

TEST(ReflectionTests, VectorIntReflectionMetadata)
{
	// Test field name and description through reflection
	const auto* field = TestObjectReflInstance["IntVector"];
	EXPECT_EQ(field->FieldName(), std::string("IntVector"));
	EXPECT_EQ(field->FieldDesc(), std::string("Vector of integers"));
}

TEST(ReflectionTests, VectorFloatReflectionMetadata)
{
	// Test field name and description for float vector through reflection
	const auto* field = TestObjectReflInstance["FloatVector"];
	EXPECT_EQ(field->FieldName(), std::string("FloatVector"));
	EXPECT_EQ(field->FieldDesc(), std::string("Vector of floats"));
}

TEST(ReflectionTests, VectorIntReflectionRoundtrip)
{
	// Test write then read returns same value through reflection
	TestObject test;
	const auto* field = TestObjectReflInstance["IntVector"];

	std::vector<int> originalVec = {7, 14, 21, 28, 35};
	field->Set(&test, &originalVec);

	const void* ptr = field->Get(&test);
	const std::vector<int>* readBack = static_cast<const std::vector<int>*>(ptr);

	EXPECT_EQ(originalVec, *readBack);
}

TEST(ReflectionTests, VectorIntReflectionEmpty)
{
	// Test with empty vector through reflection
	TestObject test;
	const auto* field = TestObjectReflInstance["IntVector"];

	std::vector<int> emptyVec;
	field->Set(&test, &emptyVec);

	EXPECT_EQ(test.IntVector.size(), 0);
	EXPECT_TRUE(test.IntVector.empty());
}

TEST(ReflectionTests, VectorIntReflectionSetNull)
{
	// Test setting a vector to null (empty vector) through reflection
	TestObject test;
	test.IntVector = {1, 2, 3};
	const auto* field = TestObjectReflInstance["IntVector"];

	field->Set(&test, nullptr);

	EXPECT_EQ(test.IntVector.size(), 0);
	EXPECT_TRUE(test.IntVector.empty());
}

// Tests for std::vector<T> specialization using direct instantiation

TEST(ReflectionTests, VectorIntDefaultValue)
{
	// Test that vector fields have correct default values
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {1, 2, 3});

	const std::vector<int>* defVal = static_cast<const std::vector<int>*>(field.DefaultValue());
	EXPECT_EQ(defVal->size(), 3);
	EXPECT_EQ((*defVal)[0], 1);
	EXPECT_EQ((*defVal)[1], 2);
	EXPECT_EQ((*defVal)[2], 3);
}

TEST(ReflectionTests, VectorFloatDefaultValue)
{
	// Test that vector fields have correct default values
	ReflectedField<std::vector<float>> field(offsetof(TestObject, FloatVector), "FloatVector", "Vector of floats", {1.1f, 2.2f, 3.3f});

	const std::vector<float>* defVal = static_cast<const std::vector<float>*>(field.DefaultValue());
	EXPECT_EQ(defVal->size(), 3);
	EXPECT_FLOAT_EQ((*defVal)[0], 1.1f);
	EXPECT_FLOAT_EQ((*defVal)[1], 2.2f);
	EXPECT_FLOAT_EQ((*defVal)[2], 3.3f);
}

TEST(ReflectionTests, VectorIntWrite)
{
	// Test writing to a vector field
	TestObject test;
	std::vector<int> newVec = {10, 20, 30, 40};
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});

	field.Set(&test, &newVec);

	EXPECT_EQ(test.IntVector.size(), 4);
	EXPECT_EQ(test.IntVector[0], 10);
	EXPECT_EQ(test.IntVector[1], 20);
	EXPECT_EQ(test.IntVector[2], 30);
	EXPECT_EQ(test.IntVector[3], 40);
}

TEST(ReflectionTests, VectorFloatWrite)
{
	// Test writing to a float vector field
	TestObject test;
	std::vector<float> newVec = {5.5f, 6.6f, 7.7f};
	ReflectedField<std::vector<float>> field(offsetof(TestObject, FloatVector), "FloatVector", "Vector of floats", {});

	field.Set(&test, &newVec);

	EXPECT_EQ(test.FloatVector.size(), 3);
	EXPECT_FLOAT_EQ(test.FloatVector[0], 5.5f);
	EXPECT_FLOAT_EQ(test.FloatVector[1], 6.6f);
	EXPECT_FLOAT_EQ(test.FloatVector[2], 7.7f);
}

TEST(ReflectionTests, VectorIntRead)
{
	// Test reading from a vector field
	TestObject test;
	test.IntVector = {100, 200, 300};
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});

	const void* ptr = field.Get(&test);
	const std::vector<int>* readVec = static_cast<const std::vector<int>*>(ptr);

	EXPECT_EQ(readVec->size(), 3);
	EXPECT_EQ((*readVec)[0], 100);
	EXPECT_EQ((*readVec)[1], 200);
	EXPECT_EQ((*readVec)[2], 300);
}

TEST(ReflectionTests, VectorFloatRead)
{
	// Test reading from a float vector field
	TestObject test;
	test.FloatVector = {11.1f, 22.2f, 33.3f, 44.4f};
	ReflectedField<std::vector<float>> field(offsetof(TestObject, FloatVector), "FloatVector", "Vector of floats", {});

	const void* ptr = field.Get(&test);
	const std::vector<float>* readVec = static_cast<const std::vector<float>*>(ptr);

	EXPECT_EQ(readVec->size(), 4);
	EXPECT_FLOAT_EQ((*readVec)[0], 11.1f);
	EXPECT_FLOAT_EQ((*readVec)[1], 22.2f);
	EXPECT_FLOAT_EQ((*readVec)[2], 33.3f);
	EXPECT_FLOAT_EQ((*readVec)[3], 44.4f);
}

TEST(ReflectionTests, VectorIntEmpty)
{
	// Test with empty vector
	TestObject test;
	std::vector<int> emptyVec;
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});

	field.Set(&test, &emptyVec);

	EXPECT_EQ(test.IntVector.size(), 0);
	EXPECT_TRUE(test.IntVector.empty());
}

TEST(ReflectionTests, VectorReadWriteRoundtrip)
{
	// Test write then read returns same value
	TestObject test;
	std::vector<int> originalVec = {7, 14, 21, 28, 35};
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});

	field.Set(&test, &originalVec);
	const void* ptr = field.Get(&test);
	const std::vector<int>* readBack = static_cast<const std::vector<int>*>(ptr);

	EXPECT_EQ(originalVec, *readBack);
}

TEST(ReflectionTests, VectorTypeSizeAndHash)
{
	// Test that vector fields have correct type size and hash
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});

	EXPECT_EQ(field.TypeSize(), sizeof(std::vector<int>));
	EXPECT_EQ(field.TypeHash(), typeid(std::vector<int>).hash_code());
}

TEST(ReflectionTests, VectorFieldOffset)
{
	// Test that vector fields report correct offset
	ReflectedField<std::vector<int>> intVecField(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});
	ReflectedField<std::vector<float>> floatVecField(offsetof(TestObject, FloatVector), "FloatVector", "Vector of floats", {});

	EXPECT_EQ(intVecField.FieldOffset(), offsetof(TestObject, IntVector));
	EXPECT_EQ(floatVecField.FieldOffset(), offsetof(TestObject, FloatVector));
}

TEST(ReflectionTests, VectorClone)
{
	// Test that cloning a vector field works correctly
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {1, 2, 3});
	auto cloned = field.Clone();

	EXPECT_NE(cloned.get(), nullptr);
	EXPECT_EQ(cloned->TypeSize(), field.TypeSize());
	EXPECT_EQ(cloned->TypeHash(), field.TypeHash());
	EXPECT_EQ(cloned->FieldName(), field.FieldName());
	EXPECT_EQ(cloned->FieldDesc(), field.FieldDesc());
}

TEST(ReflectionTests, VectorFieldMetadata)
{
	// Test field name and description
	ReflectedField<std::vector<int>> intVecField(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});
	EXPECT_EQ(intVecField.FieldName(), std::string("IntVector"));
	EXPECT_EQ(intVecField.FieldDesc(), std::string("Vector of integers"));

	ReflectedField<std::vector<float>> floatVecField(offsetof(TestObject, FloatVector), "FloatVector", "Vector of floats", {});
	EXPECT_EQ(floatVecField.FieldName(), std::string("FloatVector"));
	EXPECT_EQ(floatVecField.FieldDesc(), std::string("Vector of floats"));
}

TEST(ReflectionTests, VectorModification)
{
	// Test modifying a vector through reflection multiple times
	TestObject test;
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});

	std::vector<int> vec1 = {1, 2};
	field.Set(&test, &vec1);
	EXPECT_EQ(test.IntVector.size(), 2);

	std::vector<int> vec2 = {10, 20, 30, 40, 50};
	field.Set(&test, &vec2);
	EXPECT_EQ(test.IntVector.size(), 5);
	EXPECT_EQ(test.IntVector[4], 50);
}

TEST(ReflectionTests, VectorLargeData)
{
	// Test with a large vector
	TestObject test;
	std::vector<int> largeVec;
	for (int i = 0; i < 1000; ++i)
	{
		largeVec.push_back(i);
	}
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});

	field.Set(&test, &largeVec);
	EXPECT_EQ(test.IntVector.size(), 1000);
	EXPECT_EQ(test.IntVector[0], 0);
	EXPECT_EQ(test.IntVector[500], 500);
	EXPECT_EQ(test.IntVector[999], 999);
}

TEST(ReflectionTests, VectorSetNull)
{
	// Test setting a vector to null (empty vector)
	TestObject test;
	test.IntVector = {1, 2, 3};

	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});
	field.Set(&test, nullptr);

	EXPECT_EQ(test.IntVector.size(), 0);
	EXPECT_TRUE(test.IntVector.empty());
}

TEST(ReflectionTests, VectorRepresentation)
{
	// Test that vector field representation is correct for int elements
	ReflectedField<std::vector<int>> field(offsetof(TestObject, IntVector), "IntVector", "Vector of integers", {});

	FieldRepresentation repr = field.Representation();
	FieldRepresentation expectedRepr = GetFieldRepresentation<int>();

	// Compare the underlying representations
	auto reprVec = repr();
	auto expectedVec = expectedRepr();
	EXPECT_EQ(reprVec.size(), expectedVec.size());
	if (reprVec.size() == expectedVec.size())
	{
		for (size_t i = 0; i < reprVec.size(); ++i)
		{
			EXPECT_EQ(reprVec[i].Type, expectedVec[i].Type);
			EXPECT_EQ(reprVec[i].Name, expectedVec[i].Name);
		}
	}
}

TEST(ReflectionTests, VectorComplexElements)
{
	// Test vector with complex element types (Vector3) through reflection
	TestObject obj;
	std::vector<Vector3> vectors = {Vector3(1, 2, 3), Vector3(4, 5, 6)};

	const auto* field = TestObjectReflInstance["VectorVector"];
	EXPECT_NE(field, nullptr);

	field->Set(&obj, &vectors);

	EXPECT_EQ(obj.VectorVector.size(), 2);
	// Access individual components since Vector3 doesn't have operator==
	EXPECT_FLOAT_EQ(obj.VectorVector[0].X, 1.f);
	EXPECT_FLOAT_EQ(obj.VectorVector[0].Y, 2.f);
	EXPECT_FLOAT_EQ(obj.VectorVector[0].Z, 3.f);
	EXPECT_FLOAT_EQ(obj.VectorVector[1].X, 4.f);
	EXPECT_FLOAT_EQ(obj.VectorVector[1].Y, 5.f);
	EXPECT_FLOAT_EQ(obj.VectorVector[1].Z, 6.f);
}

TEST(ReflectionTests, VectorComplexElementsRead)
{
	// Test reading complex element types (Vector3) through reflection
	TestObject obj;
	obj.VectorVector = {Vector3(7, 8, 9), Vector3(10, 11, 12)};

	const auto* field = TestObjectReflInstance["VectorVector"];
	const void* ptr = field->Get(&obj);
	const std::vector<Vector3>* readVec = static_cast<const std::vector<Vector3>*>(ptr);

	EXPECT_EQ(readVec->size(), 2);
	EXPECT_FLOAT_EQ((*readVec)[0].X, 7.f);
	EXPECT_FLOAT_EQ((*readVec)[0].Y, 8.f);
	EXPECT_FLOAT_EQ((*readVec)[0].Z, 9.f);
	EXPECT_FLOAT_EQ((*readVec)[1].X, 10.f);
	EXPECT_FLOAT_EQ((*readVec)[1].Y, 11.f);
	EXPECT_FLOAT_EQ((*readVec)[1].Z, 12.f);
}