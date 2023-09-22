#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Algorithms
{
	/// <summary>
	/// "Fixed size array". Represents an array of type T that can be allocated one single time. Unlike std::array, the size can be defined at runtime, and not compile time.
	/// </summary>
	/// <typeparam name="T">Type of the array. Must be default initializable.</typeparam>
	template<typename T>
	class FixedArray
	{
		size_t _num;
		std::unique_ptr<T[]> _data;
	public:
		FixedArray(size_t numElements):
			_num(numElements),
			_data(std::make_unique<T[]>(numElements))
		{
		}

		FixedArray(FixedArray& c) :
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

		size_t Size()
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
			Iterator(pointer ptr): _ptr(ptr) { }

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

			friend bool operator ==(const Iterator& a, const Iterator& b) = default;
			friend bool operator !=(const Iterator& a, const Iterator& b) = default;
		};

		Iterator begin()
		{
			return Iterator(_data.get());
		}
		Iterator end()
		{
			return Iterator(_data.get() + _num);
		}
	};
}