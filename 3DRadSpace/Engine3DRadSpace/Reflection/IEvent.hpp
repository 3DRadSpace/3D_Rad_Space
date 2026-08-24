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
		/// <summary>
		/// Binds an typeless function to this event.
		/// </summary>
		/// <param name="callback">typeless callback function</param>
		virtual void Bind(std::function<Any(std::vector<Any>)> callback) = 0;
		/// <summary>
		/// Calls the bound functions with the given arguments and returns the result of the last function called.
		/// </summary>
		/// <param name="args">argument pack</param>
		/// <returns>the result of the bound function</returns>
		virtual Any operator()(std::vector<Any>& args) = 0;
		/// <summary>
		/// Unbinds the functions.
		/// </summary>
		virtual void Reset() noexcept = 0;

		virtual ~IEvent() = default;
	};
}