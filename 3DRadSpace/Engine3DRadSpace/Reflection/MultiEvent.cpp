#include "MultiEvent.hpp"

using namespace Engine3DRadSpace::Reflection;

MultiEvent::MultiEvent(std::function<Any(std::vector<Any>)> callback)
{
	_callbacks.emplace_back(callback);
}

void MultiEvent::Bind(std::function<Any(std::vector<Any>)> callback)
{
	_callbacks.emplace_back(callback);
}

Any MultiEvent::operator()(std::vector<Any> &args)
{
	std::vector<Any> results;
	for (auto& callback : _callbacks)
	{
		results.emplace_back(callback(args));
	}
	return results;
}

void MultiEvent::Reset() noexcept
{
	_callbacks.clear();
}