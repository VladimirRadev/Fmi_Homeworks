#include "MovingAverager.hpp"
MovingAverager::MovingAverager(std::string id, size_t windowSize):id(id),windowSize(windowSize){}
MovingAverager::MovingAverager(const MovingAverager& rhs):Subscriber(rhs),id(rhs.id),windowSize(rhs.windowSize){}

// method clone to make a copy of current Subscriber
Subscriber* MovingAverager::clone()const
{
	return new MovingAverager(*this);
}

// read calculates the average of the last windowSize number
// of data points
// returns 0 if there's no data points
int MovingAverager::read()const
{
	if (noDataInside == true)
	{
		return 0;
	}
	else
	{
		//here we have more required windowSize than actual received signals
		if ((unsigned int)windowSize > this->dataRecieve.size())
		{
			int sum = 0;
			for (auto x : dataRecieve)
			{
				sum += x;
			}
			return (int)(sum / dataRecieve.size());
		}
		int sum = 0;
		for (int i = dataRecieve.size()-1; i >= (int)(dataRecieve.size()-windowSize); i--)
		{
			sum += dataRecieve[i];
		}
		return (int)(sum / windowSize);
	}
}
