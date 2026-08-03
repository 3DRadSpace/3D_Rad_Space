#pragma once

enum E3DRSP_AudioError
{
	/// <summary>
	/// No error.
	/// </summary>
	E3DRSP_AudioError_None = 0,
	/// <summary>
	/// Invalid name parameter.
	/// </summary>
	E3DRSP_AudioError_BadID,
	/// <summary>
	/// Invalid enum parameter value.
	/// </summary>
	E3DRSP_AudioError_InvalidEnum,
	/// <summary>
	/// Invalid value parameter.
	/// </summary>
	E3DRSP_AudioError_InvalidValue,
	/// <summary>
	/// The function was called in an invalid context.
	/// </summary>
	E3DRSP_AudioError_InvalidOperation,
	/// <summary>
	/// Not enough memory to perform the operation.
	/// </summary>
	E3DRSP_AudioError_OutOfMemory,
	E3DRSP_AudioError_Unspecified = 0x7FFFFFFF,
};