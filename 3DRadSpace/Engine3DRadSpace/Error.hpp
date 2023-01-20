#pragma once
#include "Libs.hpp"
#include <format>

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

		void RaiseFatalError(const Error& e);
		void RaiseFatalErrorIfFailed(HRESULT result, const char* details = "",const void* extra = nullptr);
		void RaiseFatalErrorIfFalse(bool check, const char* details = "",const void* extra = nullptr);
	}
}