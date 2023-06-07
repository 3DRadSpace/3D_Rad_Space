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

	using RefTexture2D = Engine3DRadSpace::Content::AssetReference<Engine3DRadSpace::Graphics::Texture2D>;
	using RefModel3D = Engine3DRadSpace::Content::AssetReference<Engine3DRadSpace::Graphics::Model3D>;

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
	template<> FieldRepresentation GetFieldRepresentation<void>();
	template<> FieldRepresentation GetFieldRepresentation<bool>();
	template<signed_integer T> FieldRepresentation GetFieldRepresentation() { return {{FieldRepresentationType::Integer,""}}; }
	template<unsigned_integer T> FieldRepresentation GetFieldRepresentation() { return {{FieldRepresentationType::Unsigned,""}}; }
	template<std::floating_point T> FieldRepresentation GetFieldRepresentation() { return {{ FieldRepresentationType::Float,""}}; }
	template<> FieldRepresentation GetFieldRepresentation<std::string>();
	template<> FieldRepresentation GetFieldRepresentation<RefTexture2D>();
	template<> FieldRepresentation GetFieldRepresentation<RefModel3D>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Input::Key>();

	//FieldRepresentationType() specializations for mathematical types
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Vector2>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Point>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Vector3>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Vector4>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Quaternion>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Color>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::Rectangle>();
	template<> FieldRepresentation GetFieldRepresentation<Engine3DRadSpace::Math::RectangleF>();

	template<typename T>
	concept ReflectableType = requires
	{
		GetFieldRepresentation<T>();
	};
}
