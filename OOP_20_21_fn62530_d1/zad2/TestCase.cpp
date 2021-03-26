#include "TestCase.hpp"
TestCase::TestCase(const std::string& name, const Error& error) :name(name), error(error)
{
}
std::string TestCase::getName() const
{
	return this->name;
}
bool TestCase::isPassing() const
{
	if ((this->error.getType() == ErrorType::None) || (this->error.getType() == ErrorType::Warning))
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool TestCase::hasError() const
{
	if (this->error.getType() != ErrorType::None)
	{
		return true;
	}
	else
	{
		return false;
	}
}
ErrorType TestCase::getErrorType() const
{
	return this->error.getType();
}
std::string TestCase::getErrorMessage() const
{
	std::string result = "";
	if (this->error.hasMessage())
	{
		result.append(this->error.getMessage());
		return result;
	}
	else
	{
		return result;
	}
}
