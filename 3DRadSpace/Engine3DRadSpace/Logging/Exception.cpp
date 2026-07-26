#include "Exception.hpp"

Engine3DRadSpace::Logging::Exception::Exception(const std::string &err):
	_str(err),
	_stacktrace(std::stacktrace::current())
{
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