#include "Exception.hpp"

Engine3DRadSpace::Logging::Exception::Exception(const std::string &err):
	_str(err)
{
}

std::string Engine3DRadSpace::Logging::Exception::What() const
{
	return std::string(_str);
}
