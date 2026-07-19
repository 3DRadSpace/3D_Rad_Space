#pragma once
#include "IReflectedFunction.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// "Reflects" a non-member function.
	/// </summary>
	template<std::movable R, ReflectableType ...Args>
	class ReflectedFunction final : public IReflectedFunction
	{
	public:
		using Fn = R(*)(Args...);
	private:
		Fn _fn; 

		R InvokeImpl(std::span<Any> args) const
		{
			return [&]<std::size_t... Is>(std::index_sequence<Is...>)
			{
				return _fn(args[Is].Get<Args>()...);
			}(std::make_index_sequence<sizeof...(Args)>());
		}

		R InvokeImpl(std::span<void*> args) const
		{
			return[&]<std::size_t... Is>(std::index_sequence<Is...>) -> R
			{
				return _fn(*static_cast<Args*>(args[Is])...);
			}(std::make_index_sequence<sizeof...(Args)>());
		}

	public:
		ReflectedFunction(const std::string& name, Fn fn) :
			IReflectedFunction(
				sizeof...(Args),
				{GetFieldRepresentation<Args>()...},
				GetFieldRepresentation<R>(),
				name,
				typeid(Fn).name(),
				typeid(Fn)
			),
			_fn(fn)
		{
		}

		R operator()(Args&&... args)
		{
			return _fn(std::forward<Args>(args)...);
		}

		Any Invoke(void* self, std::span<Any> args) const override
		{
			(void)self;

			if constexpr(std::is_void_v<R>)
			{
				InvokeImpl(args);
				return {}; //std::any 
			}
			else return InvokeImpl(args);
		}

		const void* Get(void* objPtr) const override
		{
			return static_cast<void*>(_fn);
		}

		std::unique_ptr<IReflectedField> Clone() const override
		{
			return std::make_unique<ReflectedFunction<R, Args...>>(*this);
		}
	};
}