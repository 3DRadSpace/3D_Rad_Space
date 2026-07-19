#pragma once
#include "IEvent.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// CallbackEvent binds one single function and is cheaper than Event.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT CallbackEvent : public IEvent
	{
		std::function<Any(std::vector<Any>)> _callback;
	public:
		CallbackEvent() = default;
		CallbackEvent(std::function<Any(std::vector<Any>)> callback);

		void Bind(std::function<Any(std::vector<Any>)> callback) override;
		Any operator()(std::vector<Any> &args) override;
		void Reset() noexcept override;
	};
}