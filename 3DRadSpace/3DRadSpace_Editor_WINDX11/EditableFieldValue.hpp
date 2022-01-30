#pragma once
#include "Libs.hpp"

struct EditableFieldValue
{
	std::string Name;
	std::variant<std::string, float> Value;
};