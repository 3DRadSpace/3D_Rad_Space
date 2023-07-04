#pragma once
#include <string>
#include "../Libs.hpp"

namespace Engine3DRadSpace::Algorithms
{
	int DLLEXPORT DamerauLevenshteinDistance(const std::string& a, const std::string& b);
}