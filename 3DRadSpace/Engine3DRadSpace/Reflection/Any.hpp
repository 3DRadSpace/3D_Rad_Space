#pragma once
#include "FieldRepresentation.hpp"
#include "../Core/Tag.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// An container for any type of data.
	/// Similar to std::any, but specialized for the reflection system.
	/// </summary>
	/// <remarks>
	/// Supports small object optimisation but up to 24 bytes, as specified by the smallObjectSize constant.
	/// </remarks>
	class E3DRSP_REFLECTION_EXPORT Any
	{
		constexpr static size_t smallObjectSize = 24;
		alignas(std::max_align_t) unsigned char _storage[smallObjectSize];
		
		std::type_index _type;
		void(*_destroyFn)(void*);

		template<typename T>
		void _setDestroyFn(Tag<T> dummy)
		{
			(void)dummy;

			_destroyFn = [](void* storage)
			{
				if (sizeof(T) <= smallObjectSize)
				{
					reinterpret_cast<T*>(storage)->~T();
				}
				else
				{
					T* heapObj = *reinterpret_cast<T**>(storage);
					delete heapObj;
				}
			};
		}

	public:
		/// <summary>
		/// Creates an empty Any object.
		/// </summary>
		Any();

		/// <summary>
		/// Constructs an nothrow move constructible object of type T.
		/// </summary>
		/// <typeparam name="T">Type of the object being constructed.</typeparam>
		/// <param name="value">The value to be stored in the Any container.</param>
		template<typename T> requires std::is_nothrow_move_constructible_v<T>
		Any(T&& value) :
			_type(typeid(T))
		{
			if (sizeof(T) <= smallObjectSize)
			{
				new (_storage) T(std::forward<T>(value));
			}
			else
			{
				T* heapObj = new T(std::forward<T>(value));
				new (_storage) T* (heapObj);
			}

			_setDestroyFn<T>({});
		}

		/// <summary>
		/// Constructs an object of type T that is not nothrow move constructible.
		/// </summary>
		/// <typeparam name="T">Type of the object being constructed.</typeparam>
		/// <param name="value">The value to be stored in the Any container.</param>
		template<typename T>
		Any(T&& value) :
			_type(typeid(T))
		{
			T* heapObj = new T(std::forward<T>(value));
			new (_storage) T* (heapObj);

			_setDestroyFn<T>({});
		}

		/// <summary>
		/// Copy constructor. Performs a deep copy of the stored object, if any.
		/// </summary>
		/// <param name="other">The Any object to copy from.</param>
		Any(const Any& other);

		Any& operator=(const Any& other);
		/// <summary>
		/// Move assignment operator. Moves the stored object from the other Any, leaving it empty.
		/// </summary>
		/// <param name="other">The Any object to move from.</param>
		/// <returns>The current Any object after the move.</returns>
		Any& operator=(Any&& other) noexcept;
	
		template<typename T>
		T Get() const
		{
			if (_type != typeid(T))
			{
				throw std::bad_any_cast();
			}
			if (sizeof(T) <= smallObjectSize)
			{
				return *reinterpret_cast<T*>(_storage);
			}
			else
			{
				T* heapObj = *reinterpret_cast<T**>(_storage);
				return *heapObj;
			}
		}

		template<typename T>
		T& Get()
		{
			if (_type != typeid(T))
			{
				throw std::bad_any_cast();
			}
			if (sizeof(T) <= smallObjectSize)
			{
				return *reinterpret_cast<T*>(_storage);
			}
			else
			{
				T* heapObj = *reinterpret_cast<T**>(_storage);
				return *heapObj;
			}
		}

		void Swap(Any& other) noexcept;

		std::type_index Type() const noexcept;
		bool HasValue() const noexcept;
		
		void Reset() noexcept;
	
		~Any();
	};
}