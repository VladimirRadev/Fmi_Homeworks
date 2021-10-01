#include "Averager.hpp"
Averager::Averager(std::string id):id(id){}
Averager::Averager(const Averager& rhs):Subscriber(rhs),id(rhs.id){}

Subscriber* Averager::clone()const
{
	return new Averager(*this);
}
// read calculates the average of all data points provided so far
// returns 0 if there's no data points
int Averager::read()const
{
	if (noDataInside == true)
	{
		return 0;
	}
	else
	{
		int sum = 0;
		for (auto x : dataRecieve)
		{
			sum += x;
		}
		return (int)(sum / dataRecieve.size());
	}
}