#pragma once
#include "Subscriber.hpp"
#include "Averager.hpp"
#include "MovingAverager.hpp"
#include "PeriodicSampler.hpp"
#include <string>

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as 
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// Repository is the single place where Subscribers will
// be stored. A Repository has ownership of the Subscribers
// stored inside it.
// The only way to access the available Subscribers in the
// repository is via the Subscriber's unique id.
// id's are guaranteed to be unique
class Repository {
	std::vector<Subscriber*>subscriberCopies;
public:

	//in this class we working with dynamic copies of subscribers, not with actual objects, so then
	//we should work correct with dynamic memory
	Repository();
	Repository(const Repository& rhs);
	Repository& operator=(const Repository& rhs);
	~Repository();


	// add registers a new Subscriber in the Repository
	void add(Averager*averager);
	void add(MovingAverager*movingAverager);
	void add(PeriodicSampler*periodicSampler);

	// get returns a Subscriber in the Repository if a
	// Subscriber with the given id exists.
	// Returns nullptr otherwise
	Subscriber* get(std::string id);
}; 