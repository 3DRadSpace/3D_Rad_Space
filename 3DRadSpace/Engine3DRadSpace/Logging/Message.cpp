#include "Message.hpp"
#include <fstream>
#include <print>
#include <iostream>

using namespace Engine3DRadSpace::Logging;

Message::Message(const int32_t code, const std::string& details, const void* extra) :
	Details(details),
	Code(code),
	Extra(nullptr)
{
}

inline void Engine3DRadSpace::Logging::PrintMessage(const Message &msg)
{
	MessageHandler(msg);
}

inline void Engine3DRadSpace::Logging::PrintMessage(const std::string& msg)
{
	MessageHandler(Message(0, msg, nullptr));
}

inline void Engine3DRadSpace::Logging::DefaultMessageHandler(const Message &msg)
{
	std::fstream file("Logs.log", std::ios::app | std::ios::out | std::ios::ate); //create a file stream for writing, with append and seek end flags
	std::println(file, "{} Code {}", msg.Details, msg.Code);
	
#if _DEBUG
	std::println(std::cout, "{}", msg.Details);
#endif
	file.close();
}

inline FuncMessageHandler Engine3DRadSpace::Logging::MessageHandler = DefaultMessageHandler;