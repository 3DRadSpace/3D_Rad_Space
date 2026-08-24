#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	/// <summary>
	/// Represents an message in the logging system.
	/// </summary>
	struct E3DRSP_LOGGING_EXPORT Message
	{
		const std::string Details;
		int32_t Code;
		const void *Extra;

		Message(const int32_t code, const std::string& details, const void* extra = nullptr);
	};

	/// <summary>
	/// Handler function type for messages.
	/// </summary>
	typedef void (*FuncMessageHandler)(const Message& warning);
	/// <summary>
	///	The current message handler.
	/// </summary>
	extern FuncMessageHandler MessageHandler;

	/// <summary>
	/// Submits an message to the logging system.
	/// </summary>
	/// <param name="message">The message to submit</param>
	void E3DRSP_LOGGING_EXPORT PrintMessage(const Message &message);
	/// <summary>
	/// Submits an message to the logging system.
	/// </summary>
	/// <param name="msg">The message to submit</param>
	void E3DRSP_LOGGING_EXPORT PrintMessage(const std::string& msg);
	/// <summary>
	///	Default message handler.
	/// </summary>
	/// <param name="message">The message instance</param>
	void E3DRSP_LOGGING_EXPORT DefaultMessageHandler(const Message &message);
}