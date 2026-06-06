#pragma once
#include "IReflectedFunction.hpp"
#include "Reflection.hpp"
#include "../Core/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// An Event is an collection of function pointers that can be invoked together.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT Event
	{
		struct MemberFunctionInvoker
		{
			void* Object;
			std::unique_ptr<IReflectedFunction> Fn;
			std::type_index ReturnType;

			MemberFunctionInvoker() = default;
			MemberFunctionInvoker(void* object, std::unique_ptr<IReflectedFunction> &&fn, std::type_index returnType);
			MemberFunctionInvoker(MemberFunctionInvoker&& other) noexcept = default;

			MemberFunctionInvoker& operator=(MemberFunctionInvoker&& other) noexcept = default;
		};

		std::vector<MemberFunctionInvoker> _fns;
		bool _empty;

		void _reset();
	public:
		Event();

		template<typename R, typename O, typename F, typename ...Args>
		Event(O* object, O::F fn)
		{
			(*this) += fn;
		}

		/// <summary>
		/// Deep clone Event ctor.
		/// </summary>
		/// <param name="other">From</param>
		Event(const Event& other);
		Event(Event&&) = default;

		/// <summary>
		/// Creates a deep clone of the Event.
		/// </summary>
		/// <param name="other">From</param>
		/// <returns>Cloned event</returns>
		Event& operator=(const Event& other);
		Event& operator=(Event&&) = default;

		template<typename R, typename F, typename ...Args>
		void Bind(F fn)
		{
			MemberFunctionInvoker invoker(nullptr, std::make_unique<ReflectedFunction<R, Args...>>(typeid(F).name(), fn), typeid(R));
			_fns.emplace_back(std::move(invoker));
		}

		template<typename R, typename O, typename F, typename ...Args>
		void Bind(O* object, F fn)
		{
			MemberFunctionInvoker invoker(object, std::make_unique<ReflectedFunction<R, Args...>>(typeid(F).name(), fn), typeid(R));
			_fns.emplace_back(std::move(invoker));
		}

		void Bind(std::unique_ptr<IReflectedFunction> &&fn);

		template<typename R, typename ...Args>
		R operator()(int index, Args&& ...args)
		{
			auto fn = dynamic_cast<Reflection::ReflectedFunction<R, Args...>*>(_fns[index].Fn.get());
			return fn(std::forward<Args>(args)...);
		}

		template<typename R>
		std::vector<R> InvokeAll(std::span<std::any> args)
		{
			std::vector<R> ret;
			for(auto& fn : _fns)
			{
				ret.emplace_back(std::any_cast<R>(fn.Fn->Invoke(fn.Object, args)));
			}
			return ret;
		}

		void InvokeAllReturnless(std::span<std::span<std::any>> allArgs);
		void InvokeAllReturnless(std::span<std::span<void*>> allArgs);
		void InvokeAllReturnless();

		void Unbind(void* fnPtr);
		void UnbindAll();

		const void* operator[](size_t i) const;

		class ConstIterator
		{
			using internal_iterator = std::vector<MemberFunctionInvoker>::const_iterator;
			internal_iterator _iterator;
		public:
			using iterator_category = std::input_iterator_tag;
			using difference_type = ptrdiff_t;
			using value_type = const void*;
			using pointer = const void*;
			using reference = const void*;

			ConstIterator(internal_iterator it);

			reference operator*();
			pointer operator->();
			ConstIterator& operator++();
			ConstIterator operator++(int);

			bool operator== (const ConstIterator& a) const;
			bool operator!= (const ConstIterator& a) const;
		};

		ConstIterator cbegin() const;
		ConstIterator cend() const;

		// could use an other custom operator class that exposes the function pointer only, and not the entire details.
		using Iterator = std::vector<MemberFunctionInvoker>::iterator;

		Iterator begin();
		Iterator end();

		/// <summary>
		/// Returns the metadata of the index-th function bound in this Event instance.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		const Reflection::IReflectedFunction* ReflFnAt(size_t index);
		/// <summary>
		/// Same as <c>Event e = other.</c>
		/// </summary>
		/// <returns>Deep clone</returns>
		Event Clone() const;

		~Event() = default;
	};
}