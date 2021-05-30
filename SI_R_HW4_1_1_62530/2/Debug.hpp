#pragma once
#include <string>
class Debug
{
public:
	virtual ~Debug() = default;
	virtual std::string debug_print()const = 0;
};