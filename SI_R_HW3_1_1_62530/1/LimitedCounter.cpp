#include "LimitedCounter.hpp"
LimitedCounter::LimitedCounter(const int& max) :Counter(), max(max) {}
LimitedCounter::LimitedCounter(const int& max, const int& initial) : Counter(initial), max(max) {}
LimitedCounter::LimitedCounter(const int& max, const int& initial, const unsigned& step):Counter(initial,step),max(max){}
void LimitedCounter::increment()
{
	if ((int)(this->current + this->step) <= this->max)
	{
		this->current += this->step;
	}
	return;
}
int LimitedCounter::getMax()const
{
	return max;
}
