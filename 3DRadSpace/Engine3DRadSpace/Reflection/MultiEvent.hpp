#pragma once
#include "IEvent.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// MultiEvent is a collection of function pointers with the same return type and arguments that can be invoked together.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT MultiEvent : public IEvent
	{
		std::vector<std::function<Any(std::vector<Any>)>> _callbacks;
	public:
		/// <summary>
		/// Constructs a MultiEvent with no callbacks.
		/// </summary>
		MultiEvent() = default;
		/// <summary>
		/// Constructs a MultiEvent with a single callback.
		/// </summary>
		/// <param name="callback"></param>
		MultiEvent(std::function<Any(std::vector<Any>)> callback);

		void Bind(std::function<Any(std::vector<Any>)> callback) override;
		/// <summary>
		/// Calls all the bound functions and returns a vector of their return values.
		/// </summary>
		/// <param name="args">The arguments to pass to each bound function.</param>
		/// <returns>A vector containing the return values of each bound function.</returns>
		Any operator()(std::vector<Any> &args) override;
		/// <summary>
		/// Unbinds all the stored functions.
		/// </summary>
		void Reset() noexcept override;
	};
}