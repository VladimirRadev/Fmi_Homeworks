#include "Error.hpp"
Error::Error(const std::string& message):message(message){}
std::string Error::get_message() const
{
	return this->message;
}