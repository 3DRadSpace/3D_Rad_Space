#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Algorithms
{
	/// <summary>
	/// "Fixed size array". Represents an array of type T that can be allocated one single time. Unlike std::array, the size can be defined at runtime, and not compile time.
	/// </summary>
	/// <typeparam name="T">Type of the array. Must be default initializable.</typeparam>
	template<std::default_initializable T>
	class FixedArray
	{
		size_t _num;
		std::unique_ptr<T[]> _data;
	public:
		explicit FixedArray(size_t numElements) :
			_num(numElements),
			_data(std::make_unique<T[]>(numElements))
		{
		}

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

		FixedArray(const FixedArray& c) :
			_num(c._num),
			_data(std::make_unique<T[]>(c._num))
		{
			const size_t s = _num * sizeof(T);
			memcpy_s(_data.get(), s, c._data.get(), s);
		}

		FixedArray(FixedArray&& c) noexcept = default;

		T& operator[](unsigned i)
		{
			return _data[i];
		}

		T operator[](unsigned i) const
		{
			return _data[i];
		}

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