#pragma once
#include "IReflectedFunction.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Reflects a member function.
	/// </summary>
	/// <typeparam name="R">Return type.</typeparam>
	/// <typeparam name="O">IObject class type this function is member of</typeparam>
	/// <typeparam name="...Args">Method function arguments</typeparam>
	template<typename R, typename O, typename ...Args>
	class ReflectedMemberFunction final: public IReflectedFunction
	{
	public:
		using Fn = R(O::*)(Args...);
		using FnC = R(O::*)(Args...) const;
		using FnV = R(O::*)(Args...) volatile;
		using FnCV = R(O::*)(Args...) const volatile;

		using FnN = R(O::*)(Args...) noexcept;
		using FnCN = R(O::*)(Args...) const noexcept;
		using FnVN = R(O::*)(Args...) volatile noexcept;
		using FnCVN = R(O::*)(Args...) const volatile noexcept;
	private:
		/// intentionally avoided using std::variant.
		union MemberFunctionPointer
		{
			Fn fn;
			FnC fn_c;
			FnV fn_v;
			FnCV fn_cv;

			FnN fn_n;
			FnCN fn_cn;
			FnVN fn_vn;
			FnCVN fn_cvn;

			void* vptr;
		} _fn;

		uint8_t _fnType;

		/// <summary>
		/// Invokes the function with type-erased arguments.
		/// </summary>
		/// <param name="ptr">Object ptr.</param>
		/// <param name="args">arguments.</param>
		/// <returns>A value of type R.</returns>
		R InvokeImpl(O* ptr, std::span<Any> args) const
		{
			return [&]<std::size_t... Is>(std::index_sequence<Is...>)
			{
				switch(_fnType)
				{
					case 0: return std::invoke(_fn.fn, ptr, args[Is].Get<Args>()...);
					case 1: return std::invoke(_fn.fn_c, ptr, args[Is].Get<Args>()...);
					case 2: return std::invoke(_fn.fn_v, ptr, args[Is].Get<Args>()...);
					case 3: return std::invoke(_fn.fn_cv, ptr, args[Is].Get<Args>()...);

					case 4: return std::invoke(_fn.fn_n, ptr, args[Is].Get<Args>()...);
					case 5: return std::invoke(_fn.fn_cn, ptr, args[Is].Get<Args>()...);
					case 6: return std::invoke(_fn.fn_vn, ptr, args[Is].Get<Args>()...);
					case 7: return std::invoke(_fn.fn_cvn, ptr, args[Is].Get<Args>()...);
					default:
						std::unreachable();
				}
			}(std::make_index_sequence<sizeof...(Args)>());
		}

//Used for less code duplication.
#define RLFN_CTOR(name, type_info_param) IReflectedFunction(\
	sizeof...(Args),\
	{ GetFieldRepresentation<Args>()... },\
	GetFieldRepresentation<R>(),\
	name,\
	type_info_param.name(), \
	type_info_param \
	) 

	public:
		/// <summary>
		/// Constructs a reflected member function with the specified name and pointer.
		/// </summary>
		ReflectedMemberFunction(const std::string& name, Fn fn) : 
			RLFN_CTOR(name, typeid(Fn)),
			_fnType(0)
		{
			_fn.fn = fn;
		}

		ReflectedMemberFunction(const std::string& name, FnC fn) :
			RLFN_CTOR(name, typeid(FnC)),
			_fnType(1)
		{
			_fn.fn_c = fn;
		}

		ReflectedMemberFunction(const std::string& name, FnV fn) :
			RLFN_CTOR(name, typeid(FnV)),
			_fnType(2)
		{
			_fn.fn_v = fn;
		}

		ReflectedMemberFunction(const std::string& name, FnCV fn) :
			RLFN_CTOR(name, typeid(FnCV)),
			_fnType(3)
		{
			_fn.fn_cv = fn;
		}

		ReflectedMemberFunction(const std::string& name, FnN fn) :
			RLFN_CTOR(name, typeid(FnN)),
			_fnType(4)
		{
			_fn.fn_n = fn;
		}

		ReflectedMemberFunction(const std::string& name, FnCN fn) :
			RLFN_CTOR(name, typeid(FnCN)),
			_fnType(5)
		{
			_fn.fn_cn = fn;
		}

		ReflectedMemberFunction(const std::string& name, FnVN fn) :
			RLFN_CTOR(name, typeid(FnVN)),
			_fnType(6)
		{
			_fn.fn_vn = fn;
		}

		ReflectedMemberFunction(const std::string& name, FnCVN fn) :
			RLFN_CTOR(name, typeid(FnCVN)),
			_fnType(5)
		{
			_fn.fn_cvn = fn;
		}
#undef IRLFN_CTOR

		Any Invoke(void* self, std::span<Any> args) const override
		{
			if constexpr(std::is_void_v<R>)
			{
				InvokeImpl(static_cast<O*>(self), args);
				return {}; //std::any 
			}
			else return InvokeImpl(static_cast<O*>(self), args);
		}

		const void* Get(void* objPtr) const override
		{
			//Could be useless - this can't be used to call _fn, instead this is used for comparisions inside Engine3DRadSpace::Event.
			return _fn.vptr;
		}

		std::unique_ptr<IReflectedField> Clone() const override
		{
			switch(_fnType)
			{
				case 0: return std::make_unique<ReflectedMemberFunction<R, O, Args...>>(_name, _fn.fn);
				case 1: return std::make_unique<ReflectedMemberFunction<R, O, Args...>>(_name, _fn.fn_c);
				case 2: return std::make_unique<ReflectedMemberFunction<R, O, Args...>>(_name, _fn.fn_v);
				case 3: return std::make_unique<ReflectedMemberFunction<R, O, Args...>>(_name, _fn.fn_cv);
				case 4: return std::make_unique<ReflectedMemberFunction<R, O, Args...>>(_name, _fn.fn_n);
				case 5: return std::make_unique<ReflectedMemberFunction<R, O, Args...>>(_name, _fn.fn_cn);
				case 6: return std::make_unique<ReflectedMemberFunction<R, O, Args...>>(_name, _fn.fn_vn);
				case 7: return std::make_unique<ReflectedMemberFunction<R, O, Args...>>(_name, _fn.fn_cvn);
				default:
					std::unreachable();
			}
		}
	};
}