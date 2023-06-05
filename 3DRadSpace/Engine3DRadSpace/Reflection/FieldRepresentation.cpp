#include "FieldRepresentation.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Reflection;

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<void>()
{
	return {{ FieldRepresentationType::Unknown, ""}};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<bool>()
{
	return {{ FieldRepresentationType::Boolean, ""}};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<std::string>()
{
	return {{ FieldRepresentationType::String, ""}};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Texture2D>()
{
	return {{FieldRepresentationType::Image, ""}};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Model3D>()
{
	return {{FieldRepresentationType::Model, ""}};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Key>()
{
	return {{FieldRepresentationType::Key, ""}};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Vector2>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y" }
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Point>()
{
	return
	{
		{ FieldRepresentationType::Integer, "X"},
		{ FieldRepresentationType::Integer, "Y" }
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Vector3>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y"},
		{ FieldRepresentationType::Float, "Z"}
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Vector4>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y"},
		{ FieldRepresentationType::Float, "Z"},
		{ FieldRepresentationType::Float, "W"}
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Quaternion>() //Quaternions will be constructed from Euler angles.
{
	return {{ FieldRepresentationType::Quaternion, ""}};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Color>()
{
	return
	{
		{ FieldRepresentationType::Color, ""}
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Engine3DRadSpace::Math::Rectangle>()
{
	return
	{
		{ FieldRepresentationType::Integer, "X"},
		{ FieldRepresentationType::Integer, "Y"},
		{ FieldRepresentationType::Integer, "Width"},
		{ FieldRepresentationType::Integer, "Height"}
	};
}

template<> FieldRepresentation Engine3DRadSpace::Reflection::GetFieldRepresentation<Engine3DRadSpace::Math::RectangleF>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y"},
		{ FieldRepresentationType::Float, "Width"},
		{ FieldRepresentationType::Float, "Height"}
	};
}