#include "FieldRepresentation.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Reflection;

template<> FieldRepresentation Reflection::GetFieldRepresentation<void>()
{
	return {{ FieldRepresentationType::Unknown, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<bool>()
{
	return {{ FieldRepresentationType::Boolean, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<std::string>()
{
	return {{ FieldRepresentationType::String, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<AssetID<Texture2D>>()
{
	return {{FieldRepresentationType::Image, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<AssetID<Model3D>>()
{
	return {{FieldRepresentationType::Model, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Key>()
{
	return {{FieldRepresentationType::Key, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Vector2>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y" }
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Point>()
{
	return
	{
		{ FieldRepresentationType::Integer, "X"},
		{ FieldRepresentationType::Integer, "Y" }
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Vector3>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y"},
		{ FieldRepresentationType::Float, "Z"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Vector4>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y"},
		{ FieldRepresentationType::Float, "Z"},
		{ FieldRepresentationType::Float, "W"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Quaternion>() //Quaternions will be constructed from Euler angles.
{
	return {{ FieldRepresentationType::Quaternion, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Color>()
{
	return
	{
		{ FieldRepresentationType::Color, ""}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Math::Rectangle>()
{
	return
	{
		{ FieldRepresentationType::Integer, "X"},
		{ FieldRepresentationType::Integer, "Y"},
		{ FieldRepresentationType::Integer, "Width"},
		{ FieldRepresentationType::Integer, "Height"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<RectangleF>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y"},
		{ FieldRepresentationType::Float, "Width"},
		{ FieldRepresentationType::Float, "Height"}
	};
}