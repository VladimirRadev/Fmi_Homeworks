#include "Semaphore.hpp"
Semaphore::Semaphore() :LimitedTwowayCounter(0, 1, 0, 1){}
Semaphore::Semaphore(const bool& check):LimitedTwowayCounter(0,1,0,1)
{
	if (check == true)
	{
		this->current = 1;
	}
	else
	{
		this->current = 0;
	}


}
bool Semaphore::isAvailable()const
{
	if (this->current > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Semaphore::wait()
{
	LimitedTwowayCounter::decrement();
}
void Semaphore::signal()
{
	LimitedTwowayCounter::increment();
}
