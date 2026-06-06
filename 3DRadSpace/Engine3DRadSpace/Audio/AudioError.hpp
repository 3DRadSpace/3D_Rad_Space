#pragma once

namespace Engine3DRadSpace::Audio
{
	/// <summary>
	///	Audio error codes.
	/// </summary>
	enum class AudioError : int
	{
		/// <summary>
		/// No error.
		/// </summary>
		None = 0,
		/// <summary>
		/// Invalid name parameter.
		/// </summary>
		BadID,
		/// <summary>
		/// Invalid enum parameter value.
		/// </summary>
		InvalidEnum,
		/// <summary>
		/// Invalid value parameter.
		/// </summary>
		InvalidValue,
		/// <summary>
		/// The function was called in an invalid context.
		/// </summary>
		InvalidOperation,
		/// <summary>
		/// Not enough memory to perform the operation.
		/// </summary>
		OutOfMemory,
		Unspecified = 0x7FFFFFFF,
	};
}