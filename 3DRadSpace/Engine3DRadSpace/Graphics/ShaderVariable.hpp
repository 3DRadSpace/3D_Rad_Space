#pragma once
#include "../Reflection/IReflectedField.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT ShaderVariable final: public Reflection::IReflectedField
	{
		int _idxCbuffer;
	public:
		ShaderVariable(
			const std::string& name,
			int idxCbuffer,
			size_t offset,
			size_t size
		);

		virtual const void* Get(void* objPtr) const override;
		virtual void Set(void* objPtr, const void* value) const override;

		const void* DefaultValue() const override;
		Reflection::FieldRepresentation Representation() const override;

		int ConstantBuffer() const noexcept;

		std::unique_ptr<Reflection::IReflectedField> Clone() const override;

		~ShaderVariable() override = default;
	};
}