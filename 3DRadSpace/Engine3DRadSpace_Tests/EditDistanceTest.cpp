#include "pch.h"
#include <Engine3DRadSpace\LevenshteinDistance.hpp>

using namespace Engine3DRadSpace::Algorithms;

TEST(LevenshteinDistanceTests, Equal )
{
	EXPECT_EQ(DamerauLevenshteinDistance("Apple", "Apple"), 0);
}

TEST(LevenshteinDistanceTests, Prefix)
{
	EXPECT_EQ(DamerauLevenshteinDistance("Pineapple", "apple"), 4);
}

TEST(LevenshteinDistanceTests, Suffix)
{
	EXPECT_EQ(DamerauLevenshteinDistance("apple", "apples123"), 4);
}

TEST(LevenshteinDistanceTests, AdditionAndReplacement)
{
	EXPECT_EQ(DamerauLevenshteinDistance("matrix","matrices"), 3);
}

TEST(LevenshteinDistanceTests, AdditionDeletionAndReplacement)
{
	EXPECT_EQ(DamerauLevenshteinDistance("Sunday", "Saturday"), 3);
	EXPECT_EQ(DamerauLevenshteinDistance("Sunday", "Saturday"), 3);
}