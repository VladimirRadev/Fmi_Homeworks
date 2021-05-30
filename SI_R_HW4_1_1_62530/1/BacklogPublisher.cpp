#include "BacklogPublisher.hpp"
void BacklogPublisher::subscribe(Averager* averager)
{
	for (long unsigned int i = 0; i < this->signalsSent.size(); i++)
	{
		averager->signal(this->signalsSent[i]);
	}
	this->subscribers.push_back(averager);
}
void BacklogPublisher::subscribe(MovingAverager* movingAverager)
{
	for (long unsigned int i = 0; i < this->signalsSent.size(); i++)
	{
		movingAverager->signal(this->signalsSent[i]);
	}
	this->subscribers.push_back(movingAverager);
}
void BacklogPublisher::subscribe(PeriodicSampler* periodicSampler)
{
	for (long unsigned int i = 0; i < this->signalsSent.size(); i++)
	{
		periodicSampler->signal(this->signalsSent[i]);
	}
	this->subscribers.push_back(periodicSampler);
}