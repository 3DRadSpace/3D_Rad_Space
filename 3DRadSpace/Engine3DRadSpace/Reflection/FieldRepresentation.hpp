#pragma once
#include "../Libs.hpp"
#include "../Color.hpp"
#include "../Math/Vector4.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Rectangle.hpp"
#include "../Graphics/Texture2D.hpp"
#include "../Graphics/Model3D.hpp"
#include "../Input/Keyboard.hpp"
#include "../Concepts.hpp"
#include "../Content/AssetID.hpp"

namespace Engine3DRadSpace
{
	class IObject;
}
namespace Engine3DRadSpace::Reflection
{
	enum class FieldRepresentationType
	{
		Unknown,
		Boolean,
		Integer,
		Unsigned,
		Float,
		Quaternion,
		String,
		Image,
		Model,
		Key,
		Enum,
		Color,
		Custom,
	};

	using FieldRepresentation = std::vector<std::pair<FieldRepresentationType, const std::string>>;

	template<typename T> FieldRepresentation GetFieldRepresentation() = delete; //Only default and useer-written allow GetFieldRepresentation() specializations.

	//GetFieldRepresentation() specializations, as defined in FieldRepresentationType
	template<> DLLEXPORT FieldRepresentation GetFieldRepresentation<void>();
	template<> DLLEXPORT FieldRepresentation GetFieldRepresentation<bool>();
	template<signed_integer T> FieldRepresentation GetFieldRepresentation() { return {{FieldRepresentationType::Integer,""}}; }
	template<unsigned_integer T> FieldRepresentation GetFieldRepresentation() { return {{FieldRepresentationType::Unsigned,""}}; }
	template<std::floating_point T> FieldRepresentation GetFieldRepresentation() { return {{ FieldRepresentationType::Float,""}}; }
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<std::string>();

	template<Content::AssetType T>
	using AssetIDType = Content::AssetID<T>;

	template<AssetIDType T>
	FieldRepresentation GetFieldRepresentation() { return { {FieldRepresentationType::Custom,""} }; }
	
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Content::AssetID<Graphics::Texture2D>>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Content::AssetID<Graphics::Model3D>>();

	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Input::Key>();

	//FieldRepresentationType() specializations for mathematical types
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Vector2>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Point>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Vector3>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Vector4>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Quaternion>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Color>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Rectangle>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::RectangleF>();

	template<typename T>
	concept ReflectableType = requires
	{
		GetFieldRepresentation<T>();
	};
}
