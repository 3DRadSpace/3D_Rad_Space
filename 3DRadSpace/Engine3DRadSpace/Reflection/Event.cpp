#include "Event.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

Event::MemberFunctionInvoker::MemberFunctionInvoker(void* object, std::unique_ptr<IReflectedFunction> &&fn, std::type_index returnType) :
	Object(object),
	Fn(std::move(fn)),
	ReturnType(returnType)
{
}

void Event::_reset()
{
	_empty = true;
	_fns.clear();
}

Event::Event() :
	_empty(true)
{
}

Event::Event(const Event& other) :
	_empty(other._empty)
{
	for (const auto& fn : other._fns)
	{
		auto cloned = fn.Fn->Clone();
		std::unique_ptr<IReflectedFunction> clonedFn(static_cast<IReflectedFunction*>(cloned.release()));
		_fns.emplace_back(fn.Object, std::move(clonedFn), fn.ReturnType);
	}
}

Event& Event::operator=(const Event& other)
{
	if (this == &other) return *this;

	_empty = other._empty;
	_fns.clear();
	for (const auto& fn : other._fns)
	{
		auto cloned = fn.Fn->Clone();
		std::unique_ptr<IReflectedFunction> clonedFn(static_cast<IReflectedFunction*>(cloned.release()));
		_fns.emplace_back(fn.Object, std::move(clonedFn), fn.ReturnType);
	}
	return *this;
}

void Event::Bind(std::unique_ptr<IReflectedFunction> &&fn)
{
	if (!fn) return;
	if(_empty)
	{
		_empty = false;
	}

	_fns.emplace_back(nullptr, std::move(fn), typeid(void));
}

void Event::InvokeAllReturnless(std::span<std::span<void*>> args)
{
	int i = 0;
	for(auto argPack : args)
	{
		_fns[i++].Fn->Invoke(nullptr, _fns[i - 1].Object, argPack);
	}
}

void Event::InvokeAllReturnless(std::span<std::span<std::any>> args)
{
	int i = 0;
	for(auto argPack : args)
	{
		std::ignore = _fns[i++].Fn->Invoke(_fns[i - 1].Object, argPack);
	}
}

void Event::InvokeAllReturnless()
{
	for(auto& fn : _fns)
	{
		std::ignore = fn.Fn->Invoke(fn.Object, std::span<std::any>{});
	}
}

void Event::Unbind(void* fnPtr)
{
	std::erase_if(_fns, 
		[fnPtr](Event::MemberFunctionInvoker &fn) -> bool
		{
			return fn.Fn->Get(nullptr) == fnPtr;
		}
	);

	if(_fns.empty())
	{
		_reset();
	}
}

void Event::UnbindAll()
{
	_fns.clear();
	_reset();
}

const Event::MemberFunctionInvoker& Event::At(size_t i) const
{
	return _fns.at(i);
}

size_t Event::Count() const noexcept
{
	return _fns.size();
}

const void* Event::operator[](size_t i) const 
{
	return _fns.at(i).Fn->Get(nullptr);
}

Event::ConstIterator Event::cbegin() const
{
	return ConstIterator(_fns.cbegin());
}

Event::ConstIterator Event::cend() const
{
	return ConstIterator(_fns.end());
}

const IReflectedFunction* Event::ReflFnAt(size_t index)
{
	return _fns[index].Fn.get();
}

Event::ConstIterator::ConstIterator(internal_iterator it) : _iterator(it)
{
}

Event::ConstIterator::reference Event::ConstIterator::operator*()
{
	return _iterator.operator*().Fn->Get(nullptr);
}

Event::ConstIterator::pointer Event::ConstIterator::operator->()
{
	return _iterator.operator->()->Fn->Get(nullptr);
}

Event::ConstIterator& Event::ConstIterator::operator++()
{
	_iterator++;
	return *this;
}

Event::ConstIterator Event::ConstIterator::operator++(int)
{
	ConstIterator tmp = *this;
	++(*this);
	return tmp;
}

Event::Iterator Event::begin()
{
	return _fns.begin();
}

Event::Iterator Event::end()
{
	return _fns.end();
}

bool Event::ConstIterator::operator==(const Event::ConstIterator& e) const
{
	return _iterator == e._iterator;
}

bool Event::ConstIterator::operator!=(const Event::ConstIterator& e) const
{
	return _iterator != e._iterator;
}

Event Event::Clone() const
{
	return Event(*this);
}