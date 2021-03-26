#pragma once
#include <iostream>
#include "Error.hpp"
int Error::sizeOfStr(const char* str)
{
	int size = 0;
	while (*(str + size) != '\0')
	{
		++size;
	}
	return size;
}
Error::Error():message(nullptr),errorType(ErrorType::None)
{

}
Error::Error(const Error& rhs)
{
	delete[]this->message;
	if (!rhs.hasMessage())
	{
		this->message = nullptr;
		this->errorType = rhs.getType();
	}
	else
	{
		int sizeOfRhsMessage = sizeOfStr(rhs.getMessage());
		this->message = new char[sizeOfRhsMessage + 1];
		for (int i = 0; i < sizeOfRhsMessage; i++)
		{
			this->message[i] = rhs.getMessage()[i];
		}
		this->message[sizeOfRhsMessage] = '\0';
		this->errorType = rhs.getType();
	}
}
Error& Error::operator=(const Error& rhs)
{
	if (this != &rhs)
	{
		delete[]this->message;
		if (!rhs.hasMessage())
		{
			this->message = nullptr;
			this->errorType = rhs.getType();
		}
		else
		{
			int sizeOfRhsMessage = sizeOfStr(rhs.getMessage());
			this->message = new char[sizeOfRhsMessage + 1];
			for (int i = 0; i < sizeOfRhsMessage; i++)
			{
				this->message[i] = rhs.getMessage()[i];
			}
			this->message[sizeOfRhsMessage] = '\0';
			this->errorType = rhs.getType();
		}

	}
	return *this;
}

Error::~Error()
{
	delete[]this->message;
}
bool Error::hasMessage() const
{
	if (this->message == nullptr)
	{
		return false;
	}
	else if(sizeOfStr(this->message)>=0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

/// Retrieve the message of an error if such exists,
/// otherwise return the only "safe" invalid pointer :)
const char* Error::getMessage() const
{
	if (this->hasMessage())
	{
		return this->message;
	}
	else
	{
		return nullptr;
	}
}

/// Retrieve the type of the error
ErrorType Error::getType() const
{
	return this->errorType;
}
Error Error::newNone()
{
	Error error;
	error.message = nullptr;
	error.errorType = ErrorType::None;
	return error;

}

/// Create a new error of type BuildFailed with a message
Error Error::newBuildFailed(const char* _message)
{
	Error error;
	int sizeOfGivenStr = sizeOfStr(_message);
	delete[]error.message;
	error.message = new char[sizeOfGivenStr + 1];
	for (int i = 0; i < sizeOfGivenStr; i++)
	{
		error.message[i] = _message[i];
	}
	error.message[sizeOfGivenStr] = '\0';
	error.errorType = ErrorType::BuildFailed;
	return error;
}
Error Error::newWarning(const char* _message)
{
	Error error;
	int sizeOfGivenStr = sizeOfStr(_message);
	delete[]error.message;
	error.message = new char[sizeOfGivenStr + 1];
	for (int i = 0; i < sizeOfGivenStr; i++)
	{
		error.message[i] = _message[i];
	}
	error.message[sizeOfGivenStr] = '\0';
	error.errorType = ErrorType::Warning;
	return error;
}

Error Error::newFailedAssertion(const char* _message)
{
	Error error;
	int sizeOfGivenStr = sizeOfStr(_message);
	delete[]error.message;
	error.message = new char[sizeOfGivenStr + 1];
	for (int i = 0; i < sizeOfGivenStr; i++)
	{
		error.message[i] = _message[i];
	}
	error.message[sizeOfGivenStr] = '\0';
	error.errorType = ErrorType::FailedAssertion;
	return error;

}
