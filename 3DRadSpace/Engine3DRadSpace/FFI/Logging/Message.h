#pragma once
#include "../../Core/Libs.h"

typedef struct E3DRSP_Message
{
	const char* Details;
	int32_t Code;
	const void* Extra;
} E3DRSP_Message;

#ifdef __cplusplus
extern "C"
{
#endif
	void E3DRSP_FFI_EXPORT E3DRSP_PrintMessage(const E3DRSP_Message* message);
#ifdef __cplusplus
}
#endif