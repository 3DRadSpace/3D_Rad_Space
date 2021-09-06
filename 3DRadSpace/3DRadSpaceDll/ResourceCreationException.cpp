#include "ResourceCreationException.h"

inline ResourceCreationException::ResourceCreationException(const std::string& message, const std::type_info& type)
{
	_message = message + "Faulty type :" + std::string(type.name());
}

inline const char* ResourceCreationException::what() const
{
	return (const char*)this->_message.c_str();
}

inline ResourceCreationException::~ResourceCreationException()
{

}
