#pragma once
#include "IReflectedField.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Represents an attribute of a reflected object.
	/// </summary>
	/// <remarks>
	/// Attribute is an reflected field because ReflectedObject contains a list of IReflectedField.
	/// See Reflection.hpp for supported Attribute names.
	/// </remarks>
	class E3DRSP_REFLECTION_EXPORT Attribute : public IReflectedField
	{
	public:
		/// <summary>
		/// Constructs a attribute with the given name and value.
		/// </summary>
		/// <param name="name">The name of the attribute.</param>
		/// <param name="value">The value of the attribute.</param>
		Attribute(const std::string& name, const std::string& value);

		const void* Get(void* objPtr) const override;
		void Set(void* objPtr, const void* value) const override;

		const void* DefaultValue() const override;

		FieldRepresentation Representation() const override;

		std::unique_ptr<IReflectedField> Clone() const override;

		virtual ~Attribute() override = default;
	};
}