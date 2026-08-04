#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	struct E3DRSP_LOGGING_EXPORT Message
	{
		const std::string Details;
		int32_t Code;
		const void *Extra;

		Message(const int32_t code, const std::string& details, const void* extra = nullptr);
	};

	typedef void (*FuncMessageHandler)(const Message& warning);
	extern FuncMessageHandler MessageHandler;

	void E3DRSP_LOGGING_EXPORT PrintMessage(const Message &warning);
	void E3DRSP_LOGGING_EXPORT PrintMessage(const std::string& msg);
	void E3DRSP_LOGGING_EXPORT DefaultMessageHandler(const Message &warning);
}