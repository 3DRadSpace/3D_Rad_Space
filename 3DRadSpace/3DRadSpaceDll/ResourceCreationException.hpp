#pragma once
#include "Globals.hpp"

#pragma warning(push)
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a detailed exception thrown when resource creation and allocations fail. An alternative to std::bad_alloc.
	/// </summary>
	class DLLEXPORT ResourceCreationException : public std::exception
	{
		std::string _message;
	public:
		ResourceCreationException() = delete;
		/// <summary>
		/// Constructs a exception with the given details
		/// </summary>
		/// <param name="message">Custom message</param>
		/// <param name="type">Type of the faulty object</param>
		ResourceCreationException(const std::string& message, const std::type_info& type) :
			_message(message + "Faulty type :" + std::string(type.name())) { };

		const char* what() const override;

		~ResourceCreationException();
	};
}

#pragma warning(pop)