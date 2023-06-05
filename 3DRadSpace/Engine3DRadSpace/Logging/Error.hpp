#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	/// <summary>
	/// Represents a complete error report. Used for example in the editor frontend to output exceptions to a message box.
	/// </summary>
	struct Error
	{
		const char *Details;
		int32_t ErrorCode;
		const void *Extra;

		explicit Error(int32_t code);
		Error(int32_t code, const char *details, const void *extra = nullptr);
	};

	extern Error LastError;

	void RaiseFatalError(const Error &e);
	void RaiseFatalErrorIfFailed(HRESULT result, const char *details, const void *extra = nullptr);
	void RaiseFatalErrorIfFalse(bool check, const char *details, const void *extra = nullptr);

	inline void RaiseFatalErrorIfNull(_Post_notnull_ const void *ptr, const char *details, const void *extra = nullptr)
	{
		if (ptr == nullptr) // RaiseFatalError(Error(-1, details, extra));
		{
			LastError = Error(-1, details, extra);
			std::exit(-1);
		}
	}
}