#pragma once
#include "Globals.h"

#pragma warning(push)
#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

class DLLEXPORT ResourceCreationException : public std::exception
{
	std::string _message;
public: 
	ResourceCreationException() = delete;
	ResourceCreationException(const std::string& message, const std::type_info& type);

	const char* what() const override;

	~ResourceCreationException();
};

#pragma warning(pop)