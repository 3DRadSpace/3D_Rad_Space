#pragma once

typedef enum E3DRSP_JointType
{
	E3DRSP_JointType_Fixed = 0,
	E3DRSP_JointType_Distance = 1,
	E3DRSP_JointType_Spherical = 2,
	E3DRSP_JointType_Revolute = 3,
	E3DRSP_JointType_Prismatic = 4,
	E3DRSP_JointType_D6 = 5
} E3DRSP_JointType;
