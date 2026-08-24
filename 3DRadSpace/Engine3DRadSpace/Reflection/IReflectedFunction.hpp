#pragma once
#include "IReflectedField.hpp"
#include "Any.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Polymorphic interface for reflected functions.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT IReflectedFunction : public IReflectedField
	{
	protected:
		/// <summary>
		/// Constructs an instance of <see cref="IReflectedFunction"/>.
		/// </summary>
		/// <param name="numParams"></param>
		/// <param name="fieldInfo"></param>
		/// <param name="returnRepr"></param>
		/// <param name="name"></param>
		/// <param name="signature"></param>
		/// <param name="info"></param>
		IReflectedFunction(
			unsigned int numParams,
			std::initializer_list<FieldRepresentation> fieldInfo,
			const FieldRepresentation &returnRepr,
			const std::string& name,
			const std::string& signature,
			const std::type_info& info
		);
	
		unsigned int _numArgs;
		FieldRepresentation _returnType;
		std::vector<FieldRepresentation> _argsInfo;
		std::string _signature;

		IReflectedFunction(const IReflectedFunction&) = default;
		IReflectedFunction(IReflectedFunction&&) noexcept = default;

		IReflectedFunction& operator=(const IReflectedFunction&) = default;
		IReflectedFunction& operator=(IReflectedFunction&&) noexcept = default;

	public:
		/// <summary>
		///	Returns the number of arguments in the parameter pack.
		/// </summary>
		/// <returns>Number of arguments in this function.</returns>
		unsigned int NumParameters() const noexcept;
		/// <summary>
		/// Returns parameters metadata.
		/// </summary>
		/// <returns>Parameters representations</returns>
		const std::vector<FieldRepresentation>& ParametersInfo() const noexcept;
		/// <summary>
		/// Returns representation of the return type.
		/// </summary>
		/// <returns></returns>
		const FieldRepresentation& ReturnedTypeInfo() const noexcept;
		/// <summary>
		/// Returns the signature of the function.
		/// </summary>
		/// <returns>signature of the function</returns>
		const std::string& Signature() const noexcept;
		/// <summary>
		/// Calls the function as a member of the given object with the provided arguments.
		/// </summary>
		/// <param name="self">object</param>
		/// <param name="args">type erased argument pack</param>
		/// <returns></returns>
		virtual Any Invoke(void* self, std::span<Any> args) const = 0;

		virtual ~IReflectedFunction() = default;

		/// <summary>
		/// Does nothing. Functions aren't meant to be read as memory.
		/// </summary>
		/// <param name="objPtr">unused</param>
		const void* Get(void* objPtr) const override;
		/// <summary>
		/// Does nothing. Functions aren't meant to be written as memory.
		/// </summary>
		/// <param name="objPtr">unused.</param>
		/// <param name="value">unused.</param>
		void Set(void* objPtr, const void* value) const override;
		/// <summary>
		/// Returns nullptr. Functions don't have default values.
		/// </summary>
		/// <returns>nullptr</returns>
		const void* DefaultValue() const override;
		/// <summary>
		/// Returns an unnamed Function representation.
		/// </summary>
		/// <returns></returns>
		FieldRepresentation Representation() const override;
	};
}