#pragma once
#include "../Core/Libs.hpp"
#include "../Math/Color.hpp"
#include "../Math/Vector4.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Point.hpp"
#include "../Math/Point3.hpp"
#include "../Math/Point4.hpp"
#include "../Math/Rectangle.hpp"
#include "../Math/UPoint.hpp"
#include "../Math/UPoint3.hpp"
#include "../Math/UPoint4.hpp"
#include "../Content/Assets/TextureAsset.hpp"
#include "../Content/Assets/ModelAsset.hpp"
#include "../Content/Assets/FontAsset.hpp"
#include "../Content/Assets/SkyboxAsset.hpp"
#include "../Input/Keyboard.hpp"
#include "../Core/Concepts.hpp"
#include "../Content/AssetID.hpp"
#include "../Audio/Sound.hpp"
#include "../Objects/ObjectID.hpp"

namespace Engine3DRadSpace
{
	namespace Objects
	{
		class IObject;
	}

	namespace Audio
	{
		class Sound;
	}
	namespace Content::Assets
	{
		class TextureAsset;
		class ModelAsset;
		class FontAsset;
		class SkyboxAsset;
		class ShaderAsset;
	}
}
namespace Engine3DRadSpace::Reflection
{
	class Event;

	enum class FieldRepresentationType
	{
		None,
		Boolean,
		Integer,
		Unsigned,
		Float,
		Quaternion,
		String,
		Image,
		Model,
		Font,
		Key,
		Enum,
		Color,
		Skybox,
		Sound,
		Function,
		Event,
		ObjectID,
		Custom,
	};

	class FieldRepresentation
	{
	public:
		struct FieldRepresentationPair
		{
			FieldRepresentationType Type;
			std::string Name;
		};

		using ListFieldRepresentations = std::vector<FieldRepresentationPair>;
	protected:
		ListFieldRepresentations _values;
	public:
		FieldRepresentation(std::initializer_list<FieldRepresentationPair> pairs) noexcept : _values(pairs)
		{
		}

		FieldRepresentation(const ListFieldRepresentations& pairs) noexcept : _values(pairs)
		{
		}

		ListFieldRepresentations operator()() const noexcept
		{
			return _values;
		}

		ListFieldRepresentations::iterator begin() noexcept
		{
			return _values.begin();
		}

		ListFieldRepresentations::const_iterator begin() const noexcept
		{
			return _values.begin();
		}

		ListFieldRepresentations::iterator end() noexcept
		{
			return _values.end();
		}

		ListFieldRepresentations::const_iterator end() const noexcept
		{
			return _values.cend();
		}

		FieldRepresentationPair operator[](size_t idx) const
		{
			return _values[idx];
		}

		size_t Size() const noexcept
		{
			return _values.size();
		}
	};

	template<typename T>
	class FieldRepresentationInstance : FieldRepresentation
	{
	};

#define E3DRSP_DEFINE_FLDREPR(T, LstFieldPairs) \
	template<> \
	class FieldRepresentationInstance<T> : public FieldRepresentation \
	{ \
		public: \
			using Type = T;\
			FieldRepresentationInstance() : FieldRepresentation(ListFieldRepresentations LstFieldPairs ) {}\
	};

#define E3DRSP_DEFINE_FLDREPR_T(Specialization, LstFieldPairs) \
	template<Specialization T> \
	class FieldRepresentationInstance<T> : public FieldRepresentation \
	{ \
		public: \
			using Type = T;\
			FieldRepresentationInstance() : FieldRepresentation(ListFieldRepresentations LstFieldPairs ) {}\
	};

	E3DRSP_DEFINE_FLDREPR(void, ({{FieldRepresentationType::None, ""}}));
	E3DRSP_DEFINE_FLDREPR(bool, ({{FieldRepresentationType::Boolean,""}}));
	E3DRSP_DEFINE_FLDREPR_T(signed_integer, ({{FieldRepresentationType::Integer,""}}));
	E3DRSP_DEFINE_FLDREPR_T(unsigned_integer, ({{FieldRepresentationType::Unsigned,""}}));
	E3DRSP_DEFINE_FLDREPR_T(std::floating_point, ({{FieldRepresentationType::Float, ""}}));
	E3DRSP_DEFINE_FLDREPR(std::string, ({{FieldRepresentationType::String, ""}}));

	E3DRSP_DEFINE_FLDREPR(Content::AssetID<Content::Assets::TextureAsset>, ({{FieldRepresentationType::Image, ""}}));
	E3DRSP_DEFINE_FLDREPR(Content::AssetID<Content::Assets::ModelAsset>, ({{FieldRepresentationType::Model, ""}}));
	E3DRSP_DEFINE_FLDREPR(Content::AssetID<Content::Assets::FontAsset>, ({{FieldRepresentationType::Font, ""}}));
	E3DRSP_DEFINE_FLDREPR(Content::AssetID<Content::Assets::SkyboxAsset>, ({{FieldRepresentationType::Skybox, ""}}));
	E3DRSP_DEFINE_FLDREPR(Content::AssetID<Audio::Sound>, ({{FieldRepresentationType::Sound, ""}}));
	E3DRSP_DEFINE_FLDREPR(Input::Key, ({{FieldRepresentationType::Key}}));
	E3DRSP_DEFINE_FLDREPR(Event, ({{FieldRepresentationType::Event}}));

	//E3DRSP_DEFINE_FLDREPR_T(c_enum, ({{FieldRepresentationType::Enum}}));

	//FieldRepresentationType() specializations for mathematical types
	E3DRSP_DEFINE_FLDREPR(Math::Vector2, ({
		{FieldRepresentationType::Float, "X"},
		{FieldRepresentationType::Float, "Y"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::Vector3, ({
		{FieldRepresentationType::Float, "X"},
		{FieldRepresentationType::Float, "Y"},
		{FieldRepresentationType::Float, "Z"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::Vector4, ({
		{FieldRepresentationType::Float, "X"},
		{FieldRepresentationType::Float, "Y"},
		{FieldRepresentationType::Float, "Z"},
		{FieldRepresentationType::Float, "W"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::Quaternion, ({{FieldRepresentationType::Quaternion, ""}}));
	E3DRSP_DEFINE_FLDREPR(Math::Color, ({{FieldRepresentationType::Color, ""}}));

	E3DRSP_DEFINE_FLDREPR(Math::Rectangle, ({
		{FieldRepresentationType::Integer, "X"},
		{FieldRepresentationType::Integer, "Y"},
		{FieldRepresentationType::Integer, "Width"},
		{FieldRepresentationType::Integer, "Height"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::RectangleF, ({
		{FieldRepresentationType::Float, "X"},
		{FieldRepresentationType::Float, "Y"},
		{FieldRepresentationType::Float, "Width"},
		{FieldRepresentationType::Float, "Height"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::Matrix3x3, ({
		{FieldRepresentationType::Float, "M11"},
		{FieldRepresentationType::Float, "M12"},
		{FieldRepresentationType::Float, "M13"},

		{FieldRepresentationType::Float, "M21"},
		{FieldRepresentationType::Float, "M22"},
		{FieldRepresentationType::Float, "M23"},

		{FieldRepresentationType::Float, "M31"},
		{FieldRepresentationType::Float, "M32"},
		{FieldRepresentationType::Float, "M33"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::Matrix4x4, ({
		{FieldRepresentationType::Float, "M11"},
		{FieldRepresentationType::Float, "M12"},
		{FieldRepresentationType::Float, "M13"},
		{FieldRepresentationType::Float, "M14"},

		{FieldRepresentationType::Float, "M21"},
		{FieldRepresentationType::Float, "M22"},
		{FieldRepresentationType::Float, "M23"},
		{FieldRepresentationType::Float, "M24"},

		{FieldRepresentationType::Float, "M31"},
		{FieldRepresentationType::Float, "M32"},
		{FieldRepresentationType::Float, "M33"},
		{FieldRepresentationType::Float, "M34"},

		{FieldRepresentationType::Float, "M41"},
		{FieldRepresentationType::Float, "M42"},
		{FieldRepresentationType::Float, "M43"},
		{FieldRepresentationType::Float, "M44"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::Point, ({
		{FieldRepresentationType::Integer, "X"},
		{FieldRepresentationType::Integer, "Y"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::UPoint, ({
		{FieldRepresentationType::Unsigned, "X"},
		{FieldRepresentationType::Unsigned, "Y"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::Point3, ({
		{FieldRepresentationType::Integer, "X"},
		{FieldRepresentationType::Integer, "Y"},
		{FieldRepresentationType::Integer, "Z"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::UPoint3, ({
		{FieldRepresentationType::Unsigned, "X"},
		{FieldRepresentationType::Unsigned, "Y"},
		{FieldRepresentationType::Unsigned, "Z"}
	}));


	E3DRSP_DEFINE_FLDREPR(Math::Point4, ({
		{FieldRepresentationType::Integer, "X"},
		{FieldRepresentationType::Integer, "Y"},
		{FieldRepresentationType::Integer, "Z"},
		{FieldRepresentationType::Integer, "W"}
	}));

	E3DRSP_DEFINE_FLDREPR(Math::UPoint4, ({
		{FieldRepresentationType::Unsigned, "X"},
		{FieldRepresentationType::Unsigned, "Y"},
		{FieldRepresentationType::Unsigned, "Z"},
		{FieldRepresentationType::Unsigned, "W"}
	}));

	E3DRSP_DEFINE_FLDREPR(Objects::ObjectID, ({ {FieldRepresentationType::ObjectID, ""} }));

	template<typename T>
	concept ReflectableType = std::is_same_v<typename FieldRepresentationInstance<T>::Type, T>;

	template<ReflectableType T>
	FieldRepresentation::ListFieldRepresentations GetFieldRepresentation()
	{
		return FieldRepresentationInstance<T>()();
	}
}

#undef E3DRSP_DEFINE_FLDREPR
#undef E3DRSP_DEFINE_FLDREPR_T