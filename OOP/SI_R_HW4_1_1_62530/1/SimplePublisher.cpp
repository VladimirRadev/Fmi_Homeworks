#include "SimplePublisher.hpp"
void SimplePublisher::subscribe(Averager* averager)
{
	this->subscribers.push_back(averager);
}
void SimplePublisher::subscribe(MovingAverager* movingAverager)
{
	this->subscribers.push_back(movingAverager);
}
void SimplePublisher::subscribe(PeriodicSampler* periodicSampler)
{
	this->subscribers.push_back(periodicSampler);
}