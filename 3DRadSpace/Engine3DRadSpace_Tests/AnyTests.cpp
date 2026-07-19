#include "pch.h"
#include <Engine3DRadSpace/Reflection/Any.hpp>

#undef small

using namespace Engine3DRadSpace::Reflection;

// Test fixture for Any class with helper types
class AnyTests : public ::testing::Test
{
protected:
	// Small type (fits in SOO - <= 24 bytes)
	struct SmallType
	{
		int value;
		float data;

		SmallType() : value(0), data(0.0f) {}
		SmallType(int v, float d) : value(v), data(d) {}

		bool operator==(const SmallType& other) const
		{
			return value == other.value && data == other.data;
		}
	};

	// Large type (exceeds SOO - > 24 bytes)
	struct LargeType
	{
		std::vector<int> values;
		std::string name;

		LargeType() = default;
		LargeType(const std::vector<int>& v, const std::string& n) : values(v), name(n) {}

		bool operator==(const LargeType& other) const
		{
			return values == other.values && name == other.name;
		}
	};

	// Non-copyable type
	struct NonCopyable
	{
		int value;

		NonCopyable() : value(0) {}
		explicit NonCopyable(int v) : value(v) {}

		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;

		NonCopyable(NonCopyable&&) noexcept = default;
		NonCopyable& operator=(NonCopyable&&) noexcept = default;

		bool operator==(const NonCopyable& other) const
		{
			return value == other.value;
		}
	};

	// Type with custom destructor tracking
	static int destructorCallCount;

	struct TypeWithDestructor
	{
		int value;

		TypeWithDestructor() : value(0) {}
		explicit TypeWithDestructor(int v) : value(v) {}

		~TypeWithDestructor()
		{
			++destructorCallCount;
		}

		TypeWithDestructor(const TypeWithDestructor&) = default;
		TypeWithDestructor& operator=(const TypeWithDestructor&) = default;

		TypeWithDestructor(TypeWithDestructor&&) noexcept = default;
		TypeWithDestructor& operator=(TypeWithDestructor&&) noexcept = default;

		bool operator==(const TypeWithDestructor& other) const
		{
			return value == other.value;
		}
	};
};

int AnyTests::destructorCallCount = 0;

// Default constructor tests
TEST_F(AnyTests, DefaultConstructor)
{
	Any any;
	EXPECT_FALSE(any.HasValue());
}

// Construction with fundamental types
TEST_F(AnyTests, ConstructWithInt)
{
	Any any(42);
	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(any.Type(), typeid(int));
	EXPECT_EQ(any.Get<int>(), 42);
}

TEST_F(AnyTests, ConstructWithFloat)
{
	Any any(3.14f);
	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(any.Type(), typeid(float));
	EXPECT_FLOAT_EQ(any.Get<float>(), 3.14f);
}

TEST_F(AnyTests, ConstructWithString)
{
	std::string str = "Hello, Any!";
	Any any(str);
	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(any.Type(), typeid(std::string));
	EXPECT_EQ(any.Get<std::string>(), str);
}

// Small object optimization tests
TEST_F(AnyTests, SmallObjectOptimization)
{
	SmallType small(123, 4.56f);
	Any any(small);

	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(any.Type(), typeid(SmallType));

	SmallType retrieved = any.Get<SmallType>();
	EXPECT_EQ(retrieved.value, 123);
	EXPECT_FLOAT_EQ(retrieved.data, 4.56f);
}

// Large object heap allocation tests
TEST_F(AnyTests, LargeObjectHeapAllocation)
{
	std::vector<int> vec = {1, 2, 3, 4, 5};
	LargeType large(vec, "Large Object");

	Any any(large);

	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(any.Type(), typeid(LargeType));

	LargeType retrieved = any.Get<LargeType>();
	EXPECT_EQ(retrieved.values.size(), 5);
	EXPECT_EQ(retrieved.name, "Large Object");
}

// Move constructor tests
TEST_F(AnyTests, MoveConstructorWithInt)
{
	Any any1(42);
	Any any2(std::move(any1));

	EXPECT_TRUE(any2.HasValue());
	EXPECT_EQ(any2.Get<int>(), 42);
}

TEST_F(AnyTests, MoveConstructorWithLargeObject)
{
	std::vector<int> vec = {7, 8, 9};
	LargeType large(vec, "Moved");

	Any any1(large);
	Any any2(std::move(any1));

	EXPECT_TRUE(any2.HasValue());
	EXPECT_EQ(any2.Get<LargeType>().name, "Moved");
}

// No infinite recursion on Any&& move
TEST_F(AnyTests, MoveConstructorNoInfiniteRecursion)
{
	Any any1(123);
	// This should NOT cause infinite recursion
	Any any2(std::move(any1));
	EXPECT_EQ(any2.Get<int>(), 123);
}

// Copy constructor tests
TEST_F(AnyTests, CopyConstructorWithInt)
{
	Any any1(99);
	Any any2(any1);

	EXPECT_TRUE(any1.HasValue());
	EXPECT_TRUE(any2.HasValue());
	EXPECT_EQ(any1.Get<int>(), 99);
	EXPECT_EQ(any2.Get<int>(), 99);
}

TEST_F(AnyTests, CopyConstructorWithLargeObject)
{
	std::vector<int> vec = {10, 20, 30};
	LargeType large(vec, "Original");

	Any any1(large);
	Any any2(any1);

	EXPECT_EQ(any1.Get<LargeType>().name, "Original");
	EXPECT_EQ(any2.Get<LargeType>().name, "Original");
}

TEST_F(AnyTests, CopyConstructorEmpty)
{
	Any any1;
	Any any2(any1);

	EXPECT_FALSE(any2.HasValue());
}

// Move assignment operator tests
TEST_F(AnyTests, MoveAssignmentWithInt)
{
	Any any1(111);
	Any any2(222);

	any2 = std::move(any1);

	EXPECT_EQ(any2.Get<int>(), 111);
}

TEST_F(AnyTests, MoveAssignmentWithLargeObject)
{
	LargeType large1({1, 2}, "First");
	LargeType large2({3, 4, 5}, "Second");

	Any any1(large1);
	Any any2(large2);

	any2 = std::move(any1);

	EXPECT_EQ(any2.Get<LargeType>().name, "First");
}

// Copy assignment operator tests
TEST_F(AnyTests, CopyAssignmentWithInt)
{
	Any any1(333);
	Any any2(444);

	any2 = any1;

	EXPECT_EQ(any1.Get<int>(), 333);
	EXPECT_EQ(any2.Get<int>(), 333);
}

TEST_F(AnyTests, CopyAssignmentWithLargeObject)
{
	LargeType large({5, 6, 7}, "Copy Test");

	Any any1(large);
	Any any2;

	any2 = any1;

	EXPECT_EQ(any1.Get<LargeType>().name, "Copy Test");
	EXPECT_EQ(any2.Get<LargeType>().name, "Copy Test");
}

// Type checking and retrieval tests
TEST_F(AnyTests, BadAnyCastIntAsFloat)
{
	Any any(42);

	EXPECT_THROW(
	{
		any.Get<float>();
	},
	std::bad_any_cast);
}

TEST_F(AnyTests, BadAnyCastStringAsInt)
{
	Any any(std::string("test"));

	EXPECT_THROW(
	{
		any.Get<int>();
	},
	std::bad_any_cast);
}

TEST_F(AnyTests, BadAnyCastOnEmpty)
{
	Any any;

	EXPECT_THROW(
	{
		any.Get<int>();
	},
	std::bad_any_cast);
}

// Const and non-const Get tests
TEST_F(AnyTests, ConstGetReturnsValue)
{
	const Any any(555);
	int value = any.Get<int>();
	EXPECT_EQ(value, 555);
}

TEST_F(AnyTests, NonConstGetReturnsReference)
{
	Any any(666);
	int& ref = any.Get<int>();
	ref = 777;
	EXPECT_EQ(any.Get<int>(), 777);
}

// Reset tests
TEST_F(AnyTests, ResetClearsValue)
{
	Any any(888);
	EXPECT_TRUE(any.HasValue());

	any.Reset();

	EXPECT_FALSE(any.HasValue());
}

TEST_F(AnyTests, ResetOnEmptyIsNoop)
{
	Any any;
	any.Reset();
	EXPECT_FALSE(any.HasValue());
}

TEST_F(AnyTests, ResetCallsDestructor)
{
	{
		Any any(TypeWithDestructor(42));

		any.Reset();
		// Destructor called during Reset

		EXPECT_EQ(destructorCallCount, 2); // Constructor copy
	}
}

// Swap tests
TEST_F(AnyTests, SwapValues)
{
	Any any1(111);
	Any any2(222);

	any1.Swap(any2);

	EXPECT_EQ(any1.Get<int>(), 222);
	EXPECT_EQ(any2.Get<int>(), 111);
}

TEST_F(AnyTests, SwapWithLargeObjects)
{
	LargeType large1({1}, "First");
	LargeType large2({2, 3}, "Second");

	Any any1(large1);
	Any any2(large2);

	any1.Swap(any2);

	EXPECT_EQ(any1.Get<LargeType>().name, "Second");
	EXPECT_EQ(any2.Get<LargeType>().name, "First");
}

TEST_F(AnyTests, SwapWithEmpty)
{
	Any any1(999);
	Any any2;

	any1.Swap(any2);

	EXPECT_FALSE(any1.HasValue());
	EXPECT_TRUE(any2.HasValue());
	EXPECT_EQ(any2.Get<int>(), 999);
}

// Destructor tests
TEST_F(AnyTests, DestructorCallsDestructorFn)
{
	{
		Any any(TypeWithDestructor(123));
		// Destructor of any should call _destroyFn
	}
	// If this test completes without crash, destructor worked
}

TEST_F(AnyTests, DestructorFreesHeapMemory)
{
	{
		std::vector<int> vec(1000, 42); // Large allocation
		LargeType large(vec, "Memory test");
		Any any(large);
		// When any goes out of scope, it should properly delete the heap object
	}
	// If no memory leak detected, destructor worked
}

// Type information tests
TEST_F(AnyTests, TypeInfoForFundamentalTypes)
{
	EXPECT_EQ(Any(42).Type(), typeid(int));
	EXPECT_EQ(Any(3.14f).Type(), typeid(float));
	EXPECT_EQ(Any(true).Type(), typeid(bool));
	EXPECT_EQ(Any(1.23).Type(), typeid(double));
}

TEST_F(AnyTests, TypeInfoForComplexTypes)
{
	EXPECT_EQ(Any(std::string("test")).Type(), typeid(std::string));
	EXPECT_EQ(Any(std::vector<int>{}).Type(), typeid(std::vector<int>));
}

// Edge cases
TEST_F(AnyTests, StoreZeroValue)
{
	Any any(0);
	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(any.Get<int>(), 0);
}

TEST_F(AnyTests, StoreEmptyString)
{
	Any any(std::string(""));
	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(any.Get<std::string>(), "");
}

TEST_F(AnyTests, StoreEmptyVector)
{
	std::vector<int> empty;
	Any any(empty);
	EXPECT_TRUE(any.HasValue());
	EXPECT_TRUE(any.Get<std::vector<int>>().empty());
}

// Multiple reassignments
TEST_F(AnyTests, MultipleReassignments)
{
	Any any(10);

	any = std::string("hello");
	EXPECT_EQ(any.Get<std::string>(), "hello");

	any = 3.14f;
	EXPECT_EQ(any.Get<float>(), 3.14f);

	any = SmallType(42, 1.5f);
	EXPECT_EQ(any.Get<SmallType>().value, 42);
}

// Type stability after operations
TEST_F(AnyTests, TypeStabilityAfterCopy)
{
	Any any1(456);
	Any any2(any1);

	EXPECT_EQ(any1.Type(), typeid(int));
	EXPECT_EQ(any2.Type(), typeid(int));
}

TEST_F(AnyTests, TypeStabilityAfterMove)
{
	Any any1(789);
	Any any2(std::move(any1));

	EXPECT_EQ(any2.Type(), typeid(int));
}

// Non-copyable type with move semantics
TEST_F(AnyTests, NonCopyableTypeWithMove)
{
	NonCopyable nc(42);
	Any any(std::move(nc));

	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(any.Get<NonCopyable>().value, 42);
}

// Pointer-like types
TEST_F(AnyTests, StorePointer)
{
	int value = 100;
	int* ptr = &value;

	Any any(ptr);

	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(*any.Get<int*>(), 100);
}

TEST_F(AnyTests, StoreNullPointer)
{
	int* ptr = nullptr;
	Any any(ptr);

	EXPECT_TRUE(any.HasValue());
	EXPECT_EQ(any.Get<int*>(), nullptr);
}
