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
		void (*_destroyFn)(void*);
		void (*_copyFn)(void*, const void*);

		FieldRepresentation (*_fldRepr)();

		template<typename T>
		void _setDestroyFn(Tag<T> dummy)
		{
			(void)dummy;

			using U = std::remove_reference_t<T>;

			_fldRepr = []() -> FieldRepresentation
				{
					if constexpr (requires { ReflectableType<U>; })
					{
						return FieldRepresentationInstance<U>{};
					}
					else
					{
						return FieldRepresentation({});
					}
				};

			_destroyFn = [](void* storage)
			{
				if (sizeof(U) <= smallObjectSize)
				{
					reinterpret_cast<U*>(storage)->~U();
				}
				else
				{
					using U = std::remove_reference_t<T>;
					U* heapObj = *reinterpret_cast<U**>(storage);
					
					if(heapObj != nullptr) delete heapObj;
					heapObj = nullptr;
				}
			};

			if constexpr (std::is_copy_assignable_v<T>)
			{
				_copyFn = [](void* dst, const void* src)
				{
					using U = std::remove_reference_t<T>;
					if (sizeof(U) <= smallObjectSize)
					{
						auto left = std::launder<U>(reinterpret_cast<U*>(dst));
						const auto right = reinterpret_cast<const U*>(src);

						*left = *right;
					}
					else
					{
						auto pLeft = reinterpret_cast<U**>(dst);
						auto pRight = reinterpret_cast<const U* const*>(src);

						auto left = std::launder<U>(*pLeft);
						auto right = *pRight;

						if (!right) return;

						if (!pLeft)
						{
							pLeft = new U* ();
						}

						if (*pLeft == nullptr)
						{
							*pLeft = new U(*right);
						}
					}
				};
			}
			else
			{
				_copyFn = nullptr;
			}
		}

	public:
		/// <summary>
		/// Creates an empty Any object.
		/// </summary>
		Any();

		/// <summary>
		/// Constructs an object of type T from an rvalue reference (move constructor).
		/// </summary>
		/// <typeparam name="T">Type of the object being constructed.</typeparam>
		/// <param name="value">The value to be stored in the Any container.</param>
		template<typename T> 
		requires std::is_nothrow_move_constructible_v<T> && !std::is_same_v<std::remove_cvref_t<T>, Any>
		Any(T&& value) :
			_type(typeid(T)),
			_destroyFn(nullptr),
			_copyFn(nullptr),
			_fldRepr(nullptr)
		{
			if constexpr (sizeof(T) <= smallObjectSize)
			{
				using U = std::remove_reference_t<T>;
				new (_storage) U(std::forward<T>(value));
			}
			else
			{
				using U = std::remove_reference_t<T>;
				U* heapObj = new U(std::forward<U>(value));
				new (_storage) U* (heapObj);
			}

			_setDestroyFn<T>({});
		}

		/// <summary>
		/// Constructs an object of type T from a const lvalue reference.
		/// </summary>
		/// <typeparam name="T">Type of the object being constructed.</typeparam>
		/// <param name="value">The value to be stored in the Any container.</param>
		template<typename T>
		requires !std::is_same_v<std::remove_cvref_t<T>, Any>
		Any(const T& value) :
			_type(typeid(T)),
			_destroyFn(nullptr),
			_copyFn(nullptr),
			_fldRepr(nullptr)
		{
			if (sizeof(T) <= smallObjectSize)
			{
				new (_storage) T(value);
			}
			else
			{
				T* heapObj = new T(value);
				new (_storage) T* (heapObj);
			}

			_setDestroyFn<T>({});
		}

		/// <summary>
		/// Constructs an object of type T from a non-const lvalue reference.
		/// </summary>
		/// <typeparam name="T">Type of the object being constructed.</typeparam>
		/// <param name="value">The value to be stored in the Any container.</param>
		template<typename T>
		requires !std::is_same_v<std::remove_cvref_t<T>, Any>
		Any(T& value) :
			_type(typeid(T)),
			_destroyFn(nullptr),
			_copyFn(nullptr),
			_fldRepr(nullptr)
		{
			if (sizeof(T) <= smallObjectSize)
			{
				new (_storage) T(value);
			}
			else
			{
				T* heapObj = new T(value);
				new (_storage) T* (heapObj);
			}

			_setDestroyFn<T>({});
		}


		/// <summary>
		/// Move constructor. Moves the stored object from the other Any, leaving it empty.
		/// </summary>
		/// <param name="other">The Any object to move from.</param>
		Any(Any&& other) noexcept;

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
				return *reinterpret_cast<const T*>(_storage);
			}
			else
			{
				auto heapPtrPtr = std::launder(reinterpret_cast<const T* const*>(static_cast<const void*>(_storage)));
				return *(*heapPtrPtr);
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
				auto heapPtrPtr = std::launder(reinterpret_cast<T**>(static_cast<void*>(_storage)));
				T* heapObj = *heapPtrPtr;
				return *heapObj;
			}
		}

		void Swap(Any& other) noexcept;

		std::type_index Type() const noexcept;
		bool HasValue() const noexcept;
		
		void Reset() noexcept;
	
		FieldRepresentation GetRepresentation() const;

		~Any();
	};
}