#include "Request.hpp"
int Request::counterForAllObjects=0;

Request::Request(const std::string& message, const std::string& sender):message(message),sender(sender)
{
	Request::counterForAllObjects++;
	count = counterForAllObjects;
	ID = count;
}
std::string Request::getMessage()const
{
	return message;
}
std::string Request::getSender()const
{
	return sender;
}
int Request::getCount()const
{
	return this->count;
}
int Request::getID()const
{
	return this->ID;
}