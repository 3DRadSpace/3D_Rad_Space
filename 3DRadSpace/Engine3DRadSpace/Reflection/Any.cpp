#include "Any.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

Any::Any() :
	_type(typeid(void)),
	_destroyFn(nullptr),
	_storage()
{
}

Any::Any(const Any& other) :
	_type(other._type),
	_destroyFn(other._destroyFn),
	_storage()
{
}

Any& Any::operator=(const Any& other)
{
	if (this == &other) return *this;
	Reset();
	_type = other._type;
	_destroyFn = other._destroyFn;
	if (other.HasValue())
	{
		if (sizeof(other) <= smallObjectSize)
		{
			new (_storage) std::byte[smallObjectSize];
			std::memcpy(_storage, other._storage, smallObjectSize);
		}
		else
		{
			const void* heapObj = *reinterpret_cast<const void* const*>(other._storage);
			new (_storage) void* (const_cast<void*>(heapObj));
		}
	}
	return *this;
}

Any& Any::operator=(Any&& other) noexcept
{
	if (this == &other) return *this;
	Reset();
	_type = other._type;
	_destroyFn = other._destroyFn;
	if (other.HasValue())
	{
		if (sizeof(other) <= smallObjectSize)
		{
			new (_storage) std::byte[smallObjectSize];
			std::memcpy(_storage, other._storage, smallObjectSize);
		}
		else
		{
			void* heapObj = *reinterpret_cast<void**>(other._storage);
			new (_storage) void* (heapObj);
			*reinterpret_cast<void**>(other._storage) = nullptr;
		}
	}
	other.Reset();
	return *this;
}

void Any::Swap(Any& other) noexcept
{
	if (this == &other) return;

	Any temp(std::move(*this));
	*this = std::move(other);
	other = std::move(temp);
}

std::type_index Any::Type() const noexcept
{
	return _type;
}

bool Any::HasValue() const noexcept
{
	return _type != typeid(void);
}

void Any::Reset() noexcept
{
	if (HasValue() && _destroyFn)
	{
		_destroyFn(_storage);
	}
	_type = typeid(void);
	_destroyFn = nullptr;
}

Any::~Any()
{
	Reset();
}