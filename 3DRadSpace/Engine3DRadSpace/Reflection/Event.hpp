#pragma once
#include "IReflectedFunction.hpp"
#include "Reflection.hpp"
#include "../Core/AssetUUIDReader.hpp"
#include "IEvent.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Like MultiEvent, an Event can be bound to multiple function, but this class is also serializable in the editor.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT Event : public IEvent
	{
		struct MemberFunctionInvoker
		{
			/// <summary>
			/// Pointer to object.
			/// </summary>
			void* Object;
			/// <summary>
			/// Function reflection data.
			/// </summary>
			std::unique_ptr<IReflectedFunction> Fn;
			/// <summary>
			/// RTTI informations of the return type of Fn.
			/// </summary>
			std::type_index ReturnType;

			/// <summary>
			/// If this->Object is null then ObjectID is used to determine the object reference.
			/// </summary>
			size_t ObjectID;
			/// <summary>
			/// FunctionID is the index of the function in the reflected data of the object.
			/// </summary>
			/// <remarks>
			/// The function ID can also be identified at runtime, but that requires an O(n) search.
			/// </remarks>
			size_t FunctionID;

			/// <summary>
			/// Initializes ObjectID and FunctionID to integer maximum values to represent this struct as invalid.
			/// </summary>
			MemberFunctionInvoker();
			MemberFunctionInvoker(void* object, std::unique_ptr<IReflectedFunction> &&fn, std::type_index returnType, size_t objID, size_t fnID);

			MemberFunctionInvoker(MemberFunctionInvoker&& other) noexcept = default;
			MemberFunctionInvoker& operator=(MemberFunctionInvoker&& other) noexcept = default;
		};

		std::vector<MemberFunctionInvoker> _fns;
		bool _empty;
	public:
		Event();

		template<typename R, typename O, typename F, typename ...Args>
		Event(O* object, O::F fn)
		{
			(*this).Bind<R, F, O, Args...>(object ,fn);
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

		void Bind(std::unique_ptr<IReflectedFunction> &&fn, size_t objID, size_t fnID);

		template<typename R, typename ...Args>
		R operator()(int index, Args&& ...args)
		{
			auto fn = dynamic_cast<Reflection::ReflectedFunction<R, Args...>*>(_fns[index].Fn.get());
			return fn(std::forward<Args>(args)...);
		}

		template<typename R>
		std::vector<R> InvokeAll(std::span<Any> args)
		{
			std::vector<R> ret;
			for(auto& fn : _fns)
			{
				ret.emplace_back(fn.Fn->Invoke(fn.Object, args));
			}
			return ret;
		}

		void InvokeAll(std::span<Any> args = std::span<Any>())
		{
			for (auto& fn : _fns)
			{
				fn.Fn->Invoke(fn.Object, args);
			}
		}

		/// <summary>
		/// Unbinds the given function pointer.
		/// </summary>
		/// <param name="fnPtr">Function pointer.</param>
		void Unbind(void* fnPtr);

		/// <summary>
		/// Unbinds the idx-th function.
		/// </summary>
		/// <param name="idx">0 < idx < Count().</param>
		void Unbind(size_t idx);

		void Bind(std::function<Any(std::vector<Any>)> fn) override;
		Any operator()(std::vector<Any> &args) override;
		void Reset() noexcept override;

		const void* operator[](size_t i) const;
		const MemberFunctionInvoker& At(size_t i) const;

		size_t Count() const noexcept;

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