#include "Repository.hpp"

Repository::Repository(){}
Repository::Repository(const Repository& rhs)
{
	for (long unsigned int i = 0; i < rhs.subscriberCopies.size(); i++)
	{
		this->subscriberCopies.push_back(rhs.subscriberCopies[i]->clone());
	}
}
Repository& Repository::operator=(const Repository& rhs)
{
	if (this != &rhs)
	{
		for (auto x : this->subscriberCopies)
		{
			delete x;
		}
		this->subscriberCopies.clear();
		for (auto x : rhs.subscriberCopies)
		{
			this->subscriberCopies.push_back(x->clone());
		}
	}
	return *this;
}
Repository::~Repository()
{
	for (auto x : this->subscriberCopies)
	{
		delete x;
	}
	this->subscriberCopies.clear();
}


void Repository::add(Averager* averager)
{
	this->subscriberCopies.push_back(averager->clone());
}
void Repository::add(MovingAverager* movingAverager)
{
	this->subscriberCopies.push_back(movingAverager->clone());
}
void Repository::add(PeriodicSampler* periodicSampler)
{
	this->subscriberCopies.push_back(periodicSampler->clone());
}

Subscriber* Repository::get(std::string id)
{
	for (long unsigned int i = 0; i < this->subscriberCopies.size(); i++)
	{
		Averager* isAverager = dynamic_cast<Averager*>(this->subscriberCopies[i]);
		if (isAverager != nullptr)
		{
			if (isAverager->id == id)
			{
				return this->subscriberCopies[i];
			}
		}
		MovingAverager* isMovingAverager = dynamic_cast<MovingAverager*>(this->subscriberCopies[i]);
		if (isMovingAverager != nullptr)
		{
			if (isMovingAverager->id == id)
			{
				return this->subscriberCopies[i];
			}
		}
		PeriodicSampler* isPeriodicSampler = dynamic_cast<PeriodicSampler*>(this->subscriberCopies[i]);
		if (isPeriodicSampler != nullptr)
		{
			if (isPeriodicSampler->id == id)
			{
				return this->subscriberCopies[i];
			}
		}
	}
	return nullptr;
}