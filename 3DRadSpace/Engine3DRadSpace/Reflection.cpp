#include "Reflection.hpp"
#include "LevenshteinDistance.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;

const size_t ReflectedObject::NumObjects()
{
    return fields.size();
}

const IReflectedField* ReflectedObject::operator[](unsigned i)
{
    return fields[i];
}

const IReflectedField* ReflectedObject::operator[](const std::string& name)
{
	//First find attempt: check if field name and name exactly match.
	for (auto& field : fields)
	{
		if (field->FieldName() == name) return field;
	}

	//Second find attempt : use edit distance
	std::vector<std::pair<int, int>> v;
	for (int i = 0; i < NumObjects(); i++)
	{
		v.push_back(std::make_pair(
			Engine3DRadSpace::Algorithms::DamerauLevenshteinDistance(fields[i]->FieldName(), name),
			i
		));
	}
	std::sort(v.begin(), v.end(), 
		[](std::pair<int, int> a, std::pair<int, int> b) -> bool
		{
			return a.first < b.first;
		}
	);

	return fields[v[0].second];
}

ReflectedObject::~ReflectedObject()
{
	for (auto& field : *this)
	{
		delete field;
	}
}

std::vector<IReflectedField*>::iterator ReflectedObject::begin()
{
    return fields.begin();
}

std::vector<IReflectedField*>::iterator ReflectedObject::end()
{
    return std::prev(fields.end()); //do not return the last element, it is a ReflectedField<void>.
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<void>()
{
	return { FieldRepresentationType::Unknown };
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<bool>()
{
	return { FieldRepresentationType::Boolean };
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<std::string>()
{
	return { FieldRepresentationType::String };
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Texture2D>()
{
	return { FieldRepresentationType::Image };
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Model3D>()
{
	return { FieldRepresentationType::Model };
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Key>()
{
	return { FieldRepresentationType::Key };
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Vector2>()
{
	return
	{
		FieldRepresentationType::Float,
		FieldRepresentationType::Float
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Point>()
{
	return
	{
		FieldRepresentationType::Integer,
		FieldRepresentationType::Integer
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Vector3>()
{
	return
	{
		FieldRepresentationType::Float,
		FieldRepresentationType::Float,
		FieldRepresentationType::Float
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Vector4>()
{
	return
	{
		FieldRepresentationType::Float,
		FieldRepresentationType::Float,
		FieldRepresentationType::Float,
		FieldRepresentationType::Float
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Quaternion>() //Quaternions will be constructed from Euler angles.
{
	return
	{
		FieldRepresentationType::Float,
		FieldRepresentationType::Float,
		FieldRepresentationType::Float
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Color>()
{
	return
	{
		FieldRepresentationType::Color
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Engine3DRadSpace::Math::Rectangle>()
{
	return
	{
		FieldRepresentationType::Integer,
		FieldRepresentationType::Integer,
		FieldRepresentationType::Integer,
		FieldRepresentationType::Integer
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Engine3DRadSpace::Math::RectangleF>()
{
	return
	{
		FieldRepresentationType::Float,
		FieldRepresentationType::Float,
		FieldRepresentationType::Float,
		FieldRepresentationType::Float
	};
}

ReflectedObject::ReflectedObject(const std::string& name, const std::string& category, const std::string& desc, std::initializer_list<IReflectedField*> obj_fields) :
	Name(name),
	fields(obj_fields),
	Category(category),
	Description(desc)
{

}