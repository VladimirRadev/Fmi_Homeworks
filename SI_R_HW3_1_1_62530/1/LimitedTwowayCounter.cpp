#include "LimitedTwowayCounter.hpp"
LimitedTwowayCounter::LimitedTwowayCounter(const int& min, const int& max)
	:Counter(),TwowayCounter(),LimitedCounter(max),min(min){}
LimitedTwowayCounter::LimitedTwowayCounter(const int& min, const int& max, const int& initial)
	:Counter(initial),TwowayCounter(initial),LimitedCounter(max,initial),min(min){}
LimitedTwowayCounter::LimitedTwowayCounter(const int& min, const int& max, const int& initial, const unsigned& step)
	: Counter(initial, step), TwowayCounter(initial, step), LimitedCounter(max, initial, step), min(min){}
void LimitedTwowayCounter::increment()
{
	LimitedCounter::increment();
}
void LimitedTwowayCounter::decrement()
{
	if ((int)(this->current - this->step) >= this->min)
	{
		this->current -= this->step;
	}
	return;
}
int LimitedTwowayCounter::getMin()const
{
	return min;
}