#include "Error.hpp"
#include <cstdlib>

Engine3DRadSpace::Logging::Error Engine3DRadSpace::Logging::LastError{S_OK,"Everything is fine :)"};

void Engine3DRadSpace::Logging::RaiseFatalError(const Error& e)
{
	LastError = e;
	std::exit(e.ErrorCode);
}

void Engine3DRadSpace::Logging::RaiseFatalErrorIfFailed(HRESULT result, const char* details,const void* extra)
{
	if (FAILED(result)) RaiseFatalError(Error(result, details, extra));
}

void Engine3DRadSpace::Logging::RaiseFatalErrorIfFalse(bool check, const char* details,const void* extra)
{
	if (!check) RaiseFatalError(Error(-1, details, extra));
}