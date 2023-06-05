#include "Exception.hpp"

Engine3DRadSpace::Logging::Exception::Exception(const std::string &err):
	_str(err)
{
}

std::string &Engine3DRadSpace::Logging::Exception::What()
{
	return _str;
}
