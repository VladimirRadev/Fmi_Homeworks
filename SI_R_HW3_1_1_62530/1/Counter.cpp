#include "Counter.hpp"
Counter::Counter() :initial(0), step(1),current(0) {}
Counter::Counter(const int& initial) : initial(initial), step(1),current(initial){};
Counter::Counter(const int& initial, const unsigned& step):initial(initial),step(step),current(initial){}
void Counter::increment()
{
	this->current += step;
}
int Counter::getTotal()const
{
	return current;
}
const unsigned Counter::getStep()const
{
	return step;
}