#pragma once
#include "IReflectedField.hpp"

namespace Engine3DRadSpace::Reflection
{
	class E3DRSP_REFLECTION_EXPORT Attribute : public IReflectedField
	{
	public:
		Attribute(const std::string& name, const std::string& value);

		const void* Get(void* objPtr) const override;
		void Set(void* objPtr, const void* value) const override;

		const void* DefaultValue() const override;

		FieldRepresentation Representation() const override;

		std::unique_ptr<IReflectedField> Clone() const override;

		virtual ~Attribute() override = default;
	};
}