#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Algorithms
{
	/// <summary>
	/// "Fixed size array". Represents an array of type T that can be allocated one single time. Unlike std::array, the size can be defined at runtime, and not compile time.
	/// Compared to <c>std::unique_ptr&lt;T[]&gt;</c>, interators are supported.
	/// </summary>
	/// <typeparam name="T">Type of the array. Must be default initializable.</typeparam>
	template<std::default_initializable T>
	class FixedArray
	{
		size_t _num;
		std::unique_ptr<T[]> _data;
	public:
		/// <summary>
		/// Creates T[numElements].
		/// </summary>
		/// <param name="numElements">Number of elements</param>
		explicit FixedArray(size_t numElements) :
			_num(numElements),
			_data(std::make_unique<T[]>(numElements))
		{
		}

		/// <summary>
		/// Copies elements from an initializer list.
		/// </summary>
		/// <param name="lst">Initializer list</param>
		FixedArray(std::initializer_list<T> lst)
		{
			_num = std::distance(lst.begin(), lst.end());
			_data = std::make_unique<T[]>(_num);

			for (int i = 0; auto e : lst)
			{
				_data[i] = e;
				i++;
			}
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="c">Object to be copied.</param>
		FixedArray(const FixedArray& c) :
			_num(c._num),
			_data(std::make_unique<T[]>(c._num))
		{
			const size_t s = _num * sizeof(T);
			memcpy_s(_data.get(), s, c._data.get(), s);
		}

		/// <summary>
		/// Move constructor. Default since FixedArray<T> uses an underlying std::unique_ptr<T[]>.
		/// </summary>
		/// <param name="c"></param>
		FixedArray(FixedArray&& c) noexcept = default;

		/// <summary>
		/// Gets the i-th element. No bound checking.
		/// </summary>
		/// <param name="i">Index</param>
		/// <returns>lvalue to the i-th element</returns>
		T& operator[](unsigned i)
		{
			return _data[i];
		}
		
		/// <summary>
		/// Returns a copy of the i-th element.
		/// </summary>
		/// <param name="i">Index</param>
		/// <returns>Copy of the i-th element</returns>
		T operator[](unsigned i) const
		{
			return _data[i];
		}

		/// <summary>
		/// Returns the number of elements.
		/// </summary>
		/// <returns>Number of elements.</returns>
		size_t Size() const
		{
			return _num;
		}

		struct Iterator
		{
		public:
			using iterator_category = std::contiguous_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;
		private:
			pointer _ptr;

		public:
			explicit Iterator(pointer ptr) : _ptr(ptr) { }

			reference operator*() const
			{
				return *_ptr;
			}
			pointer operator->()
			{
				return _ptr;
			}
			Iterator& operator++() //Prefix increment
			{
				_ptr++;
				return *this;
			}
			Iterator operator++(int) //Postfix increment
			{
				Iterator tmp = *this;
				++(*this);
				return tmp;
			}

			Iterator operator+(int i)
			{
				return Iterator(_ptr + i);
			}

			Iterator operator-(int i)
			{
				return Interator(_ptr - i);
			}

			Iterator& operator+=(int i)
			{
				_ptr += i;
				return *this;
			}
			Iterator& operator -=(int i)
			{
				_ptr -= i;
				return *this;
			}

			bool operator ==( const Iterator& i) const = default;
			bool operator !=(const Iterator& i) const = default;
		};

		Iterator begin()
		{
			return Iterator(_data.get());
		}
		Iterator end()
		{
			return Iterator(static_cast<T*>(_data.get()) + _num);
		}
	};
}