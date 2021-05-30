#pragma once
#include "Message.hpp"
#include "Subscriber.hpp"
#include <vector>
#include <string>

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as 
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// Averager is a type of Subscriber, which saves data and
// returns the average of the data when `read()` is called.
// Data is provided with the `signal()` method.
// Average of N numbers = sum(all numbers) / N
class Averager :public Subscriber{
public:
	Averager(std::string id);
	Averager(const Averager& rhs);

	// id is a unique identifier for a Subscriber
	// Should never be changed once initialized
	const std::string id;


	// method clone to make a copy of current Subscriber
	Subscriber* clone()const override;


	// read calculates the average of all data points provided so far
	// returns 0 if there's no data points
	int read()const override;
};