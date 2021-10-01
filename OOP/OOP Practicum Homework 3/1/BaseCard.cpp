/**
* Solution to homework assignment 3
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Vladimir Radev
* @idnumber 62530
* @task 1
* @compiler VC
*/
#include "BaseCard.hpp"
BaseCard::BaseCard(const std::string& name, const std::string& effect)
{
	setName(name);
	setEffect(effect);
}
void BaseCard::setName(const std::string& name)
{
	this->name = name;
}
std::string BaseCard::getName()const
{
	return this->name;
}
void BaseCard::setEffect(const std::string& effect)
{
	this->effect = effect;
}
std::string BaseCard::getEffect()const
{
	return this->effect;

}
