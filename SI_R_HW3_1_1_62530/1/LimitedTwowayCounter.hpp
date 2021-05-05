#pragma once
#include "Counter.hpp"
#include "LimitedCounter.hpp"
#include "TwowayCounter.hpp"
class LimitedTwowayCounter :public TwowayCounter, public LimitedCounter
{
protected:
	int min;
public:
	LimitedTwowayCounter(const int& min, const int& max);
	LimitedTwowayCounter(const int& min, const int& max, const int& initial);
	LimitedTwowayCounter(const int& min, const int& max, const int& initial, const unsigned& step);
	void increment()override;
	void decrement()override;
	int getMin()const;

};