#pragma once
#include "IReflectedField.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Represents a variable of unknown type.
	/// <summary>
	class E3DRSP_REFLECTION_EXPORT UnknownVariable final : public IReflectedField
	{
	public:
		UnknownVariable(
			size_t offset,
			size_t size,
			const std::string& name,
			const std::string& desc
		);

		const void* Get(void* objPtr) const override;
		void Set(void* objPtr, const void* value) const override;

		const void* DefaultValue() const override;

		FieldRepresentation Representation() const override;

		std::unique_ptr<IReflectedField> Clone() const override;

		~UnknownVariable() override = default;
	};
}