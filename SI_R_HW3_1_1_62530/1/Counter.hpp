#pragma once

class Counter
{
protected:
	int initial;
	unsigned step;
	int current;
public:
	Counter();
	Counter(const int& initial);
	Counter(const int& initial, const unsigned& step);
	virtual void increment();
	int getTotal()const;
	const unsigned getStep()const;


};