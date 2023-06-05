#include "Error.hpp"

Engine3DRadSpace::Logging::Error Engine3DRadSpace::Logging::LastError{S_OK,"Everything is fine :)"};

Engine3DRadSpace::Logging::Error::Error(int32_t code) : Details(std::move(std::format("Error code : {}", code).c_str())), ErrorCode(code), Extra(nullptr)
{
};

Engine3DRadSpace::Logging::Error::Error(int32_t code, const char *details, const void *extra) :
	Details(details), ErrorCode(code), Extra(extra)
{
}

void Engine3DRadSpace::Logging::RaiseFatalError(const Error &e)
{
	LastError = e;
	std::exit(e.ErrorCode);
}

void Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(HRESULT result, const char* details, const void* extra)
{
	if (FAILED(result)) RaiseFatalError(Error(result, details, extra));
}

void Engine3DRadSpace::Logging::RaiseFatalErrorIfFalse(bool check, const char *details, const void *extra)
{
	if (!check) RaiseFatalError(Error(-1, details, extra));
}