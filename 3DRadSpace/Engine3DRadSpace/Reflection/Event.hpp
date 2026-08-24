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
			MemberFunctionInvoker() :
				Object(nullptr),
				Fn(nullptr),
				ReturnType(typeid(void)),
				ObjectID(static_cast<size_t>(-1)),
				FunctionID(static_cast<size_t>(-1))
			{
			}
			/// <summary>
			/// Creates a valid MemberFunctionInvoker with the given parameters.
			/// </summary>
			/// <param name="object"></param>
			/// <param name="fn"></param>
			/// <param name="returnType"></param>
			/// <param name="objID"></param>
			/// <param name="fnID"></param>
			MemberFunctionInvoker(
				void* object,
				std::unique_ptr<IReflectedFunction> &&fn,
				std::type_index returnType,
				size_t objID = static_cast<size_t>(-1),
				size_t fnID = static_cast<size_t>(-1)
			) :
				Object(object),
				Fn(std::move(fn)),
				ReturnType(returnType),
				ObjectID(objID),
				FunctionID(fnID)
			{
			}
			MemberFunctionInvoker(size_t objID, size_t fnID) :
				MemberFunctionInvoker(nullptr, nullptr, typeid(void), objID, fnID)
			{
			}

			MemberFunctionInvoker(MemberFunctionInvoker&& other) noexcept = default;
			MemberFunctionInvoker& operator=(MemberFunctionInvoker&& other) noexcept = default;
		};

		std::vector<MemberFunctionInvoker> _fns;
		bool _empty = true;
	public:
		/// <summary>
		/// Constructs a empty Event.
		/// </summary>
		Event();

		/// <summary>
		/// Constructs a Event with the given method.
		/// </summary>
		/// <typeparam name="R">Return type</typeparam>
		/// <typeparam name="O">Class type of the method</typeparam>
		/// <typeparam name="F">Method type</typeparam>
		/// <typeparam name="...Args">Argument pack for the method</typeparam>
		/// <param name="object">object instance</param>
		/// <param name="fn">member function pointer</param>
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
		/// <summary>
		/// Move constructor for this Event.
		/// </summary>
		/// <param name="other"></param>
		Event(Event&& other) = default;

		/// <summary>
		/// Creates a deep clone of the Event.
		/// </summary>
		/// <param name="other">From</param>
		/// <returns>Cloned event</returns>
		Event& operator=(const Event& other);
		Event& operator=(Event&&) = default;

		/// <summary>
		/// Binds the given function to this event.
		/// </summary>
		/// <typeparam name="R">Return type</typeparam>
		/// <typeparam name="F">Function type</typeparam>
		/// <typeparam name="...Args">Function parameter pack</typeparam>
		/// <param name="fn">Function pointer</param>
		template<typename R, typename F, typename ...Args>
		void Bind(F fn)
		{
			MemberFunctionInvoker invoker(nullptr, std::make_unique<ReflectedFunction<R, Args...>>(typeid(F).name(), fn), typeid(R), -1, -1);
			_fns.emplace_back(std::move(invoker));
		}

		/// <summary>
		/// Binds a member function to this event.
		/// </summary>
		/// <typeparam name="R">Return type</typeparam>
		/// <typeparam name="O">Object type</typeparam>
		/// <typeparam name="F">Function type</typeparam>
		/// <typeparam name="...Args">Argument pack</typeparam>
		/// <param name="object">Object pointer</param>
		/// <param name="fn">Member function pointer</param>
		template<typename R, typename O, typename F, typename ...Args>
		void Bind(O* object, F fn)
		{
			MemberFunctionInvoker invoker(object, std::make_unique<ReflectedFunction<R, Args...>>(typeid(F).name(), fn), typeid(R));
			_fns.emplace_back(std::move(invoker));
		}

		/// <summary>
		/// Binds an typeless function to this event.
		/// </summary>
		/// <param name="fn">Function reflection data</param>
		/// <param name="objID">Object ID in the ObjectList.</param>
		/// <param name="fnID">Function ID</param>
		void Bind(std::unique_ptr<IReflectedFunction> &&fn, size_t objID, size_t fnID);
		/// <summary>
		/// Binds an function by finding it in the ObjectList and reflection metadata.
		/// </summary>
		/// <param name="objID">object ID from an object list</param>
		/// <param name="fnID">function ID in metadata</param>
		void BindIncomplete(size_t objID, size_t fnID);

		/// <summary>
		/// Calls the index-th bound function.
		/// </summary>
		/// <typeparam name="R">Return type</typeparam>
		/// <typeparam name="...Args">Argument pack</typeparam>
		/// <param name="index">Index of the function</param>
		/// <param name="...args">Argument pack</param>
		/// <returns>The result of the function</returns>
		template<typename R, typename ...Args>
		R operator()(int index, Args&& ...args)
		{
			auto fn = dynamic_cast<Reflection::ReflectedFunction<R, Args...>*>(_fns[index].Fn.get());
			return fn(std::forward<Args>(args)...);
		}
		/// <summary>
		/// Invokes all functions
		/// </summary>
		/// <typeparam name="R">Return type</typeparam>
		/// <param name="args">Type erased argument pack</param>
		/// <returns>A list of returned values</returns>
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
		/// <summary>
		/// Invokes all functions ignoring the return value.
		/// </summary>
		/// <param name="args">Type erased argument pack</param>
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
		/// <summary>
		/// Binds the given function pointer to this event.
		/// </summary>
		/// <param name="fn">Type erased function</param>
		void Bind(std::function<Any(std::vector<Any>)> fn) override;
		/// <summary>
		/// Calls all the functions with the specified argument pack.
		/// </summary>
		/// <param name="args">type erased argument pack</param>
		/// <returns>List of return values</returns>
		Any operator()(std::vector<Any> &args) override;
		/// <summary>
		/// Clears all the bound functions.
		/// </summary>
		void Reset() noexcept override;
		/// <summary>
		/// Returns an raw pointer to the i-th bound function.
		/// </summary>
		/// <param name="i">index</param>
		/// <returns>type erased function or member function pointer</returns>
		const void* operator[](size_t i) const;
		/// <summary>
		/// Returns an invoker at the specified index.
		/// </summary>
		/// <param name="i">index</param>
		/// <returns>Structure containing function metadata</returns>
		const MemberFunctionInvoker& At(size_t i) const;
		/// <summary>
		/// Returns the number of bound functions.
		/// </summary>
		/// <returns></returns>
		size_t Count() const noexcept;

		/// <summary>
		/// Wraps the vector iterator with a const iterator to prevent modification of the bound functions.
		/// </summary>
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
		/// <summary>
		/// Const begin iterator for this event.
		/// </summary>
		/// <returns>const begin iterator</returns>
		ConstIterator cbegin() const;
		/// <summary>
		/// Const end iterator for this event
		/// </summary>
		/// <returns>const end iterator</returns>
		ConstIterator cend() const;

		// could use an other custom operator class that exposes the function pointer only, and not the entire details.
		using Iterator = std::vector<MemberFunctionInvoker>::iterator;
		/// <summary>
		/// Begin iterator for this event.
		/// </summary>
		/// <returns>std::vector<MemberFunctionInvoker>::iterator::begin()</returns>
		Iterator begin();
		/// <summary>
		/// End iterator for this event
		/// </summary>
		/// <returns>std::vector<MemberFunctionInvoker>::iterator::end()</returns>
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