#include "ResourceCreationException.h"

inline const char* Engine3DRadSpace::ResourceCreationException::what() const
{
	return (const char*)this->_message.c_str();
}

inline Engine3DRadSpace::ResourceCreationException::~ResourceCreationException()
{

}
