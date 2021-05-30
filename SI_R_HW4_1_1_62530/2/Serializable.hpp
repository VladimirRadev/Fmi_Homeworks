#pragma once
#include <string>
class Serializable
{
public:
	virtual ~Serializable() = default;
	virtual std::string to_string()const = 0;
	virtual void from_string(const std::string& source)=0;

};