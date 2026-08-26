#pragma once
#include "../../Math/Color.h"
#include "../../Math/Vector3.h"

typedef struct E3DRSP_DirectionalLight
{
	E3DRSP_Color LightColor;
	E3DRSP_Color AmbientColor;
	E3DRSP_Vector3 LightDirection;
	float Intensity;
} E3DRSP_DirectionalLight;