#include "pch.h"
#include "MyTestEnum.hpp"

REFL_ENUM_BEGIN(MyTestEnum, "MyTestEnum")
	REFL_ENUM_ENTRY("None", MyTestEnum::None)
	REFL_ENUM_ENTRY("Apple", MyTestEnum::Apple)
	REFL_ENUM_ENTRY("Pineapple", MyTestEnum::Pineapple)
	REFL_ENUM_ENTRY("Strawberry", MyTestEnum::Strawberry)
REFL_ENUM_END

TEST(EnumReflection, ReflEnumData)
{
	EXPECT_EQ(MyTestEnumEnumReflInstance.NumberOfEntries(), 4u);
	EXPECT_EQ(MyTestEnumEnumReflInstance.TypeHashCode(), typeid(MyTestEnum).hash_code());
}

TEST(EnumReflection, ReflQueries)
{
	std::array<std::pair<std::string, int>, 4> entries =
	{
		std::pair("None",0),
		std::pair("Apple",1),
		std::pair("Pineapple",2),
		std::pair("Strawberry", 3)
	};

	for (int i = 0; auto p : entries)
	{
		EXPECT_EQ(MyTestEnumEnumReflInstance[i].VisibleName, p.first);
		EXPECT_EQ(MyTestEnumEnumReflInstance[i].Value, p.second);

		i++;
	}
}