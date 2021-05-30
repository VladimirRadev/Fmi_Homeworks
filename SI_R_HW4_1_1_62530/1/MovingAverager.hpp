#pragma once
#include "Message.hpp"
#include <string>
#include "Subscriber.hpp"

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as 
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// MovingAverager is a type of Subscriber, which saves data
// and returns the average of the last `windowSize` number of
// data points when `read()` is called.
// Data is provided with the `signal()` method.
// Average of N numbers = sum(all numbers) / N
class MovingAverager:public Subscriber {
public:
	MovingAverager(std::string id, size_t windowSize);
	MovingAverager(const MovingAverager& rhs);

	// id is a unique identifier for a Subscriber
	// Should never be changed once initialized
	const std::string id;

	// windowSize specifies how many most-recent data points
	// should be saved
	// Should never be changed once initialized
	const size_t windowSize;


	// method clone to make a copy of current Subscriber
	Subscriber* clone()const override;


	// read calculates the average of the last windowSize number
	// of data points
	// returns 0 if there's no data points
	int read()const override;
};