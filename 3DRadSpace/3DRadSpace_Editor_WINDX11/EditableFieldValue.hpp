#pragma once
#include "Libs.hpp"

struct EditableFieldValue
{
	__stdstring Name;
	std::variant<__stdstring,float> Value;
};