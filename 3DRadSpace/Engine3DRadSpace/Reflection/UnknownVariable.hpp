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
		/// <summary>
		/// Constructs an instance of a UnknownVariable with the given parameters.
		/// </summary>
		/// <param name="offset">Memory offset</param>
		/// <param name="size">Size in bytes</param>
		/// <param name="name">Field name</param>
		/// <param name="desc">Field description</param>
		UnknownVariable(
			size_t offset,
			size_t size,
			const std::string& name,
			const std::string& desc
		);
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="objPtr">unused</param>
		/// <returns>nullptr</returns>
		const void* Get(void* objPtr) const override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="objPtr">unused</param>
		/// <param name="value">unused</param>
		void Set(void* objPtr, const void* value) const override;
		/// <summary>
		/// Returns nullptr
		/// </summary>
		/// <returns>nullptr</returns>
		const void* DefaultValue() const override;
		/// <summary>
		/// Returns an empty FieldRepresentation.
		/// </summary>
		/// <returns>Empty representation</returns>
		FieldRepresentation Representation() const override;
		/// <summary>
		/// Performs a deep clone of this UnknownVariable instance.
		/// </summary>
		/// <returns></returns>
		std::unique_ptr<IReflectedField> Clone() const override;

		~UnknownVariable() override = default;
	};
}