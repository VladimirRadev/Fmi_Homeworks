#pragma once
#include "Counter.hpp"
class LimitedCounter:virtual public Counter
{
protected:
	int max;
public:
	LimitedCounter(const int& max);
	LimitedCounter(const int& max, const int& initial);
	LimitedCounter(const int& max, const int& initial, const unsigned& step);
	void increment()override;
	int getMax()const;
};
