#include "PeriodicSampler.hpp"
PeriodicSampler::PeriodicSampler(std::string id, size_t period):period(period),id(id){}
PeriodicSampler::PeriodicSampler(const PeriodicSampler& rhs):Subscriber(rhs),period(rhs.period),id(rhs.id){}


// method clone to make a copy of current Subscriber
Subscriber* PeriodicSampler::clone()const
{
	return new PeriodicSampler(*this);
}


// read returns the latest period-th data point if such exists
// 0 otherwise
int PeriodicSampler::read()const
{
	if (noDataInside == true)
	{
		return 0;
	}
	else
	{
		int result = 0;
		for (int i = dataRecieve.size()-1; i >=0; --i)
		{
			if (i % period == 0)
			{
				result = dataRecieve[i];
				break;
			}
		}
		return result;
	}
}