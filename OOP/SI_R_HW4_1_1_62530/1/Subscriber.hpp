#pragma once
#include <vector>
#include <string>
#include "Message.hpp"
class Subscriber
{
protected:
	bool noDataInside;
	std::vector<int>dataRecieve;
public:
	Subscriber();

	Subscriber(const Subscriber& rhs);

	virtual ~Subscriber() = default;
	// signal adds a new data point
	virtual void signal(Message);


	//method clone to make a copy of current Subscriber
	virtual Subscriber* clone()const = 0;

	// read calculates the average of all data points provided so far
	// returns 0 if there's no data points
	virtual int read()const=0;
};