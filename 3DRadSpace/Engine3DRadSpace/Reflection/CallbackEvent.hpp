#pragma once
#include "IEvent.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// CallbackEvent bind one single function and is cheaper than Event.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT CallbackEvent : public IEvent
	{
		std::function<Any(std::vector<Any>)> _callback;
	public:
		/// <summary>
		/// Creates a CallbackEvent with no callback bound.
		/// </summary>
		CallbackEvent() = default;
		/// <summary>
		/// Creates a CallbackEvent with the given callback function.
		/// </summary>
		/// <param name="callback">The callback function to bind to the event.</param>
		explicit CallbackEvent(std::function<Any(std::vector<Any>)> callback);
		/// <summary>
		/// Bounds the given function to this instance.
		/// </summary>
		/// <param name="callback">callback function</param>
		void Bind(std::function<Any(std::vector<Any>)> callback) override;
		/// <summary>
		/// Calls the bound function
		/// </summary>
		/// <param name="args">Arguments pack</param>
		/// <returns>Return value wrapped in an Any type erased container.</returns>
		Any operator()(std::vector<Any> &args) override;
		/// <summary>
		///	Unbinds the function from this instance.
		/// </summary>
		void Reset() noexcept override;
	};
}