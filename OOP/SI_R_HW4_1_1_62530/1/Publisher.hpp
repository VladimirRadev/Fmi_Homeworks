#pragma once
#include <vector>
#include "Subscriber.hpp"
#include "Averager.hpp"
#include "MovingAverager.hpp"
#include "PeriodicSampler.hpp"
class Publisher
{
protected:
	//we won't working with dynamic memory inside this class Because we get a reference of objects (not dynamic copy of them)
	//and we don't care about deleting memory, outside world should delete dynamic memory
	std::vector<Subscriber*>subscribers;
	std::vector<Message> signalsSent;

public:
	virtual ~Publisher() = default;
	// subscribe registers a Subscriber to start receiving messages
	virtual void subscribe(Averager*)=0;
	virtual void subscribe(MovingAverager*)=0;
	virtual void subscribe(PeriodicSampler*)=0;

	// unsubscribe removes a Subscriber from the Publisher
	// Subscribers are removed based on their `id`
	// id's will always be unique
	virtual void unsubscribe(Averager*);
	virtual void unsubscribe(MovingAverager*);
	virtual void unsubscribe(PeriodicSampler*);

	// signal receives a message from an external source
	// and replays that message to all the current subscribers
	virtual void signal(Message);
};
