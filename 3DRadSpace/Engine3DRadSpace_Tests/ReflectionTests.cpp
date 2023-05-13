#include "pch.h"
#include <Engine3DRadSpace/Reflection.hpp>
#include <Engine3DRadSpace/IObject.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Input;

class TestObject : public IObject
{
public:
	TestObject() : IObject("Test object"), Integer(5), Float(1.0f)
	{
	}

	// Inherited via IObject
	virtual void Initialize() override
	{
	}
	virtual void Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt) override
	{
	}
	virtual void Draw(Engine3DRadSpace::Math::Matrix& view, Engine3DRadSpace::Math::Matrix& projection, double dt) override
	{
	}
	virtual void EditorInitialize() override
	{
	}
	virtual void EditorDraw(const Engine3DRadSpace::Math::Matrix& view, const Engine3DRadSpace::Math::Matrix& projection, double dt) override
	{
	}

	int Integer;
	float Float;
	Color Colour;
	Math::Rectangle Rectangle1;
	RectangleF Rectangle2;

	Vector4 Vector;
	Key TestKey;
};

__REFL_BEGIN(TestObject, "Test Object", "Tests", "Dummy test object")
__REFL_FIELD(TestObject, std::string, Name, "Name", "Test object", "Name of the object")
__REFL_FIELD(TestObject, std::string, Tag, "Tag", "", "Object tag")
__REFL_FIELD(TestObject, std::string, Resource, "Resource", "", "Object resource file")
__REFL_FIELD(TestObject, bool, Enabled, "Enabled", true, "Is the object enabled?")
__REFL_FIELD(TestObject, bool, Visible, "Visible", true, "Is the object visible?")
__REFL_FIELD(TestObject, Vector3, Position, "Position", Vector3::Zero(), "Object position in world")
__REFL_FIELD(TestObject, Vector3, RotationCenter, "Rotation center", Vector3::Zero(), "Rotation pivot point")
__REFL_FIELD(TestObject, Quaternion, Rotation, "Rotation", Quaternion(), "Rotation")
__REFL_FIELD(TestObject, Vector3, Scale, "Scale", Vector3::One(), "Object scale")
__REFL_FIELD(TestObject, int, Integer, "Test Integer", 5, "int32_t value used for testing")
__REFL_FIELD(TestObject, float, Float, "Test float", 1.0f, "test float value")
__REFL_FIELD(TestObject, Color, Colour, "Test color", Colors::White, "test color")
__REFL_FIELD(TestObject, Math::Rectangle, Rectangle1, "Test rectangle 1", Math::Rectangle(1, 2, 3, 4), "integer rectangle")
__REFL_FIELD(TestObject, RectangleF, Rectangle2, "Test rectangle 2", RectangleF(5, 4, 3, 2), "float rectangle")
__REFL_FIELD(TestObject, Vector4, Vector, "Vector4", Vector4(0, 0, 0, 1), "Test vector4")
__REFL_FIELD(TestObject, Key, TestKey, "Test key", Key::ESC, "Dummy test key")
__REFL_END

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

TEST(ReflectionTests, NameRW) //ReflectionTests : Name read-write
{
	TestObject test;

	std::string n2 = "test name string"; //Create a temporary string used to assign the test instance.
	TestObjectReflInstance[0]->Set(&test, &n2); //test.Name = n2 (by using the reflection methods
	
	EXPECT_EQ(n2, test.Name); //Check if name was successfully set.
	EXPECT_EQ(*static_cast<std::string*>(TestObjectReflInstance[0]->Get(&test)), n2); //Check if the name can be read using the reflection interface.
	//Same goes on for the next tests.
}

TEST(ReflectionTests, TagRW)
{
	TestObject test;

	std::string ntag = "test tag";
	TestObjectReflInstance[1]->Set(&test, &ntag);

	EXPECT_EQ(ntag, test.Tag);
	EXPECT_EQ(*static_cast<std::string*>(TestObjectReflInstance[1]->Get(&test)),ntag);
}

TEST(ReflectionTests, ResourceRW)
{
	TestObject test;

	std::string nresource = "pic.png";
	TestObjectReflInstance[2]->Set(&test, &nresource);

	EXPECT_EQ(nresource, test.Resource);
	EXPECT_EQ(*static_cast<std::string*>(TestObjectReflInstance[2]->Get(&test)), nresource);
}

TEST(ReflectionTests, EnabledRW)
{
	TestObject test;
	test.Enabled = true;

	bool e = false;
	TestObjectReflInstance[3]->Set(&test, &e);

	EXPECT_EQ(e, test.Enabled);
	EXPECT_EQ(*static_cast<bool*>(TestObjectReflInstance[3]->Get(&test)), e);
}

TEST(ReflectionTests, VisibleRW)
{
	TestObject test;
	test.Visible = true;

	bool v = false;
	TestObjectReflInstance[4]->Set(&test, &v);

	EXPECT_EQ(v, test.Visible);
	EXPECT_EQ(*static_cast<bool*>(TestObjectReflInstance[4]->Get(&test)), v);
}

TEST(ReflectionTests, PositionRW)
{
	TestObject test;
	
	Vector3 p(2, 3, 4);
	TestObjectReflInstance[5]->Set(&test, &p);

	EXPECT_EQ(p, test.Position);
	EXPECT_EQ(*static_cast<Vector3*>(TestObjectReflInstance[5]->Get(&test)), p);
}

TEST(ReflectionTests, RotationCenter)
{
	TestObject test;

	Vector3 pivot(5, 5, 5);
	TestObjectReflInstance[6]->Set(&test, &pivot);

	EXPECT_EQ(pivot, test.RotationCenter);
	EXPECT_EQ(*static_cast<Vector3*>(TestObjectReflInstance[6]->Get(&test)), pivot);
}

TEST(ReflectionTests, RotationRW)
{
	TestObject test;

	Quaternion q(1, 2, 3, 4);
	TestObjectReflInstance[7]->Set(&test, &q);

	EXPECT_EQ(q, test.Rotation);
	EXPECT_EQ(*static_cast<Quaternion*>(TestObjectReflInstance[7]->Get(&test)), q);
}

TEST(ReflectionTests, ScaleRW)
{
	TestObject test;

	Vector3 scale(3, 3, 3);
	TestObjectReflInstance[8]->Set(&test, &scale);

	EXPECT_EQ(scale, test.Scale);
	EXPECT_EQ(*static_cast<Vector3*>(TestObjectReflInstance[8]->Get(&test)), scale);
}

TEST(ReflectionTests, IntegerRW)
{
	TestObject test;

	int i = 67;
	TestObjectReflInstance[9]->Set(&test, &i);

	EXPECT_EQ(i, test.Integer);
	EXPECT_EQ(*static_cast<int*>(TestObjectReflInstance[9]->Get(&test)), i);
}

TEST(ReflectionTests, FloatRW)
{
	TestObject test;

	float f = 3.141f;
	TestObjectReflInstance[10]->Set(&test, &f);

	EXPECT_EQ(f, test.Float);
	EXPECT_EQ(*static_cast<float*>(TestObjectReflInstance[10]->Get(&test)), f);
}

TEST(ReflectionTests, ColorRW)
{
	TestObject test;

	Color c = Colors::Red;
	TestObjectReflInstance[11]->Set(&test, &c);

	EXPECT_EQ(c, test.Colour);
	EXPECT_EQ(*static_cast<Color*>(TestObjectReflInstance[11]->Get(&test)), c);
}

TEST(ReflectionTests, RectangleRW)
{
	TestObject test;

	Math::Rectangle r(10, 20, 30, 40);
	TestObjectReflInstance[12]->Set(&test, &r);

	EXPECT_EQ(r, test.Rectangle1);
	EXPECT_EQ(*static_cast<Math::Rectangle*>(TestObjectReflInstance[12]->Get(&test)), r);
}

TEST(ReflectionTests, RectangleFRW)
{
	TestObject test;

	RectangleF r(4, 5, 3, 8);
	TestObjectReflInstance[13]->Set(&test, &r);

	EXPECT_EQ(r, test.Rectangle2);
	EXPECT_EQ(*static_cast<RectangleF*>(TestObjectReflInstance[13]->Get(&test)), r);
}

TEST(ReflectionTests, Vector4RW)
{
	TestObject test;

	Vector4 v(4, 3, 2, 1);
	TestObjectReflInstance[14]->Set(&test, &v);
	
	EXPECT_EQ(v, test.Vector);
	EXPECT_EQ(*static_cast<Vector4*>(TestObjectReflInstance[14]->Get(&test)), v);
}

TEST(ReflectionTests, KeyRW)
{
	TestObject test;

	Key k = Key::Enter;
	TestObjectReflInstance[15]->Set(&test, &k);

	EXPECT_EQ(k, test.TestKey);
	EXPECT_EQ(*static_cast<Key*>(TestObjectReflInstance[15]->Get(&test)), k);
}