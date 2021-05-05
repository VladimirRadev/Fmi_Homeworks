#pragma once
#include <string>
class Request
{
private:
	std::string message;
	std::string sender;
	static int counterForAllObjects;
	int count;
	int ID;
public:
	Request(const std::string& message, const std::string& sender);
	std::string getMessage()const;
	std::string getSender()const;
	int getCount()const;
    int getID()const;
	
};