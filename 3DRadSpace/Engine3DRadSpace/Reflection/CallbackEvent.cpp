#include "CallbackEvent.hpp"

using namespace Engine3DRadSpace::Reflection;

CallbackEvent::CallbackEvent(std::function<Any(std::vector<Any>)> callback)
	: _callback(callback)
{
}

void CallbackEvent::Bind(std::function<Any(std::vector<Any>)> callback)
{
	_callback = callback;
}

Any CallbackEvent::operator()(std::vector<Any> &args)
{
	if (_callback)
	{
		return _callback(args);
	}
	else
	{
		throw std::runtime_error("Callback not bound.");
	}
}

void CallbackEvent::Reset() noexcept
{
	_callback = {};
}