#include "Event.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

Event::MemberFunctionInvoker::MemberFunctionInvoker(
	void* object, 
	std::unique_ptr<IReflectedFunction> &&fn,
	std::type_index returnType,
	size_t objID,
	size_t fnID
) :
	Object(object),
	Fn(std::move(fn)),
	ReturnType(returnType),
	ObjectID(objID),
	FunctionID(objID)
{
}

Event::MemberFunctionInvoker::MemberFunctionInvoker(size_t objID, size_t fnID) :
	Object(nullptr),
	Fn(nullptr),
	ReturnType(typeid(void)),
	ObjectID(objID),
	FunctionID(fnID)
{
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
		_fns.emplace_back(fn.Object, std::move(clonedFn), fn.ReturnType, fn.ObjectID, fn.FunctionID);
	}
}

Event& Event::operator=(const Event& other)
{
	if (this == &other) return *this;

	_empty = other._empty;
	_fns.clear();
	for (const auto& fn : other._fns)
	{
		if (fn.Fn)
		{
			auto cloned = fn.Fn->Clone();
			std::unique_ptr<IReflectedFunction> clonedFn(static_cast<IReflectedFunction*>(cloned.release()));
			_fns.emplace_back(fn.Object, std::move(clonedFn), fn.ReturnType, fn.ObjectID, fn.FunctionID);
		}
		else
		{
			_fns.emplace_back(fn.Object, nullptr, fn.ReturnType, fn.ObjectID, fn.FunctionID);
		}
	}
	return *this;
}

void Event::Bind(std::unique_ptr<IReflectedFunction> &&fn, size_t objID, size_t fnID)
{
	if (!fn) return;
	if(_empty)
	{
		_empty = false;
	}

	_fns.emplace_back(nullptr, std::move(fn), typeid(void), objID, fnID);
}

void Event::Unbind(void* fnPtr)
{
	std::erase_if(_fns,
		[fnPtr](Event::MemberFunctionInvoker &fn) -> bool
		{
			return fn.Fn->Get(nullptr) == fnPtr;
		}
	);
}

void Event::Unbind(size_t idx)
{
	_fns.erase(_fns.begin() + idx);

	if(_fns.empty())
	{
		Reset();
	}
}

void Event::Reset() noexcept
{
	_empty = true;
	_fns.clear();
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

Any Event::operator()(std::vector<Any> &args)
{
	std::vector<Any> r;

	for (auto& fn : _fns)
	{
		r.emplace_back(fn.Fn->Invoke(fn.Object, args));
	}

	return r;
}

void Event::Bind(std::function<Any(std::vector<Any>)> fnargs)
{
	
}

void Event::BindIncomplete(size_t objID, size_t fnID)
{
	_fns.emplace_back(objID, fnID);
}