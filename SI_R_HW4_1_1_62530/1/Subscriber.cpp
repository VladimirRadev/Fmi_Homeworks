#include "Subscriber.hpp"
Subscriber::Subscriber() :noDataInside(true){}
Subscriber::Subscriber(const Subscriber& rhs)
{
	this->noDataInside = rhs.noDataInside;
	if (this->noDataInside == false)
	{
		for (auto x : rhs.dataRecieve)
		{
			this->dataRecieve.push_back(x);
		}
	}
}
void Subscriber::signal(Message newMessage)
{
	if (noDataInside == true)
	{
		noDataInside = false;
		dataRecieve.push_back(newMessage.data);
		return;
	}
	dataRecieve.push_back(newMessage.data);
	return;
}