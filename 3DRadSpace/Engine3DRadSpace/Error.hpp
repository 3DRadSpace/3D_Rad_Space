#pragma once
#include "Libs.hpp"
#include <format>
#include <sal.h>

namespace Engine3DRadSpace
{
	namespace Logging
	{
		/// <summary>
		/// Represents a complete error report. Used for example in the editor frontend to output exceptions to a message box.
		/// </summary>
		struct Error
		{
			const char* Details;
			int32_t ErrorCode;
			const void* Extra;

			Error(int32_t code) : Details(std::move(std::format("Error code : {}", code).c_str())), ErrorCode(code), Extra(nullptr) {};
			Error(int32_t code, const char* details, const void* extra = nullptr) : Details(details), ErrorCode(code), Extra(extra) {};
		};

		extern Error LastError;

		inline void RaiseFatalError(const Error& e)
		{
			LastError = e;
			std::exit(e.ErrorCode);
		}

		inline void RaiseFatalErrorIfFailed(HRESULT result, const char* details, const void* extra = nullptr)
		{
			if (FAILED(result)) RaiseFatalError(Error(result, details, extra));
		}

		inline void RaiseFatalErrorIfFalse(bool check, const char* details, const void* extra = nullptr)
		{
			if (!check) RaiseFatalError(Error(-1, details, extra));
		}
		inline void RaiseFatalErrorIfNull( _Post_notnull_ const void* ptr, const char* details, const void* extra = nullptr)
		{
			if (ptr == nullptr) // RaiseFatalError(Error(-1, details, extra));
			{
				LastError = Error(-1, details, extra);
				std::exit(-1);
			}
		}
	}
}