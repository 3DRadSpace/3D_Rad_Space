#include "Exception.hpp"
#include <csignal>

Engine3DRadSpace::Logging::Exception::Exception(const std::string &err):
	_str(err),
	_stacktrace(std::stacktrace::current())
{
#if _DEBUG
	#if _WIN32
		DebugBreak();
	#elif _LINUX
		std::raise(SIGTRAP);
	#endif
#endif
}

std::string Engine3DRadSpace::Logging::Exception::What() const
{
	return std::string(_str);
}

const char* Engine3DRadSpace::Logging::Exception::what() const
{
	return this->_str.c_str();
}

const std::stacktrace& Engine3DRadSpace::Logging::Exception::GetStacktrace() const noexcept
{
	return _stacktrace;
}