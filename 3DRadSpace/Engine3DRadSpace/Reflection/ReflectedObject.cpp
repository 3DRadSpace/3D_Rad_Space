#include "ReflectedObject.hpp"
#include "../Algorithms/LevenshteinDistance.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;

const size_t ReflectedObject::NumFields()
{
    return _fields.size()  - 1;
}

const IReflectedField* ReflectedObject::operator[](unsigned i)
{
    return _fields[i];
}

const IReflectedField* ReflectedObject::operator[](const std::string& name)
{
	//First find attempt: check if field name and name exactly match. O(#fields)
	for (auto& field : _fields)
	{
		if (field->FieldName() == name) return field;
	}

	//Second find attempt : use edit distance. O(n*m*fields)
	std::vector<std::pair<int, int>> v;
	for (int i = 0; i < NumFields(); i++)
	{
		v.push_back(std::make_pair(
			Engine3DRadSpace::Algorithms::DamerauLevenshteinDistance(_fields[i]->FieldName(), name),
			i
		));
	}
	std::sort(v.begin(), v.end(), 
		[](std::pair<int, int> a, std::pair<int, int> b) -> bool
		{
			return a.first < b.first;
		}
	);

	return _fields[v[0].second];
}

std::vector<IReflectedField *>::iterator ReflectedObject::begin()
{
	return _fields.begin();
}

std::vector<IReflectedField *>::iterator ReflectedObject::end()
{
	return std::prev(_fields.end()); //do not return the last element, it is a ReflectedField<void>.
}

ReflectedObject::~ReflectedObject()
{
	for (auto& field : *this)
	{
		delete field;
	}
}