#pragma once
#include "Any.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Base interface for an Event.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT IEvent
	{
	protected:
		IEvent() = default;
	public:
		virtual void Bind(std::function<Any(std::vector<Any>)> callback) = 0;
		virtual Any operator()(std::vector<Any>& args) = 0;
		virtual void Reset() noexcept = 0;

		virtual ~IEvent() = default;
	};
}