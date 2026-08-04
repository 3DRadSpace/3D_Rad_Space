#include "Message.h"
#include "../../Logging/Message.hpp"

using namespace Engine3DRadSpace::Logging;

void E3DRSP_PrintMessage(const E3DRSP_Message* message)
{
	PrintMessage(Message(
		message->Code,
		message->Details,
		message->Extra
	)
	);
}