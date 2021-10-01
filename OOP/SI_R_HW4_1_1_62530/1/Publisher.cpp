#include "Publisher.hpp"
void Publisher::unsubscribe(Averager* averager)
{
	for (long unsigned int i = 0; i < this->subscribers.size(); i++)
	{
		Averager* isAverager = dynamic_cast<Averager*>(this->subscribers[i]);
		if (isAverager != nullptr)
		{
			if (isAverager->id == averager->id)
			{
				this->subscribers.erase(this->subscribers.begin() + i);
				break;
			}
		}

	}
}
void Publisher::unsubscribe(MovingAverager* movinAverager)
{
	for (long unsigned int i = 0; i < this->subscribers.size(); i++)
	{
		MovingAverager* isMovingAverager = dynamic_cast<MovingAverager*>(this->subscribers[i]);
		if (isMovingAverager != nullptr)
		{
			if (isMovingAverager->id == movinAverager->id)
			{
				this->subscribers.erase(this->subscribers.begin() + i);
				break;
			}
		}

	}
}
void Publisher::unsubscribe(PeriodicSampler* periodicSampler)
{

	for (long unsigned int i = 0; i < this->subscribers.size(); i++)
	{
		PeriodicSampler* isPeriodicSampler = dynamic_cast<PeriodicSampler*>(this->subscribers[i]);
		if (isPeriodicSampler != nullptr)
		{
			if (isPeriodicSampler->id == periodicSampler->id)
			{
				this->subscribers.erase(this->subscribers.begin() + i);
				break;
			}
		}

	}
}

// signal receives a message from an external source
// and replays that message to all the current subscribers
void Publisher::signal(Message messageToSent)
{
	for (auto x : this->subscribers)
	{
		x->signal(messageToSent);
	}
	this->signalsSent.push_back(messageToSent);

}