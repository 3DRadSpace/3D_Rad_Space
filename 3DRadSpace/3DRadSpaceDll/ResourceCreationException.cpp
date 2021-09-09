#include "ResourceCreationException.h"

inline const char* ResourceCreationException::what() const
{
	return (const char*)this->_message.c_str();
}

inline ResourceCreationException::~ResourceCreationException()
{

}
