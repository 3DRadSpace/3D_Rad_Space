#pragma once
#include "../Math/Vector3.h"

typedef struct E3DRSP_Listener
{
	float Volume;
	E3DRSP_Vector3 Position;
	E3DRSP_Vector3 Velocity;

	E3DRSP_Vector3 Direction;
	E3DRSP_Vector3 Normal;

	bool Enabled;
} E3DRSP_Listener;