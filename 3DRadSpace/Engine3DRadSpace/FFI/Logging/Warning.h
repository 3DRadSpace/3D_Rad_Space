#pragma once
#include "../../Core/Libs.h"

typedef struct E3DRSP_Warning
{
	const char* Details;
	int32_t Code;
	int Severity;
	const void* Extra;
} E3DRSP_Warning;

#ifdef __cplusplus
extern "C"
{
#endif
	void E3DRSP_FFI_EXPORT E3DRSP_PrintWarning(const E3DRSP_Warning* warning);
#ifdef __cplusplus
}
#endif