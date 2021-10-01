#pragma once
#include "LimitedTwowayCounter.hpp"
class Semaphore:public LimitedTwowayCounter
{
public:
	Semaphore();
	Semaphore(const bool&);
	bool isAvailable()const;
	void wait();
	void signal();
};