#pragma once
#include "../Libs.hpp"
#include "../Color.hpp"
#include "../Math/Vector4.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Rectangle.hpp"
#include "../Graphics/Texture2D.hpp"
#include "../Graphics/Model3D.hpp"
#include "../Input/Keyboard.hpp"
#include "../Content/AssetReference.hpp"

namespace Engine3DRadSpace
{
	class IObject;
}
namespace Engine3DRadSpace::Reflection
{
	template<typename N>
	concept signed_integer = std::is_same_v<N, int8_t> || std::is_same_v<N, int16_t> || std::is_same_v<N, int32_t> || std::is_same_v<N, int64_t>;

	template<typename N>
	concept unsigned_integer = std::is_same_v<N, uint8_t> || std::is_same_v<N, uint16_t> || std::is_same_v<N, uint32_t> || std::is_same_v<N, uint64_t>;

	using RefTexture2D = Content::AssetReference<Graphics::Texture2D>;
	using RefModel3D = Content::AssetReference<Graphics::Model3D>;

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
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<RefTexture2D>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<RefModel3D>();
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
