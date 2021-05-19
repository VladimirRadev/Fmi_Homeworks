/**
* Solution to homework assignment 4
* Object Oriented Programming Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2020/2021
*
* @author Vladimir Radev
* @idnumber 62530
* @task 1
* @compiler VC
*/
#include "Card.hpp"
Card::Card(const std::string& name, const std::string& effect, const unsigned int& rarity)
{
	this->setName(name);
	this->setEffect(effect);
	this->setRarity(rarity);
}
void Card::setName(const std::string& name)
{
	this->name = name;
}
std::string Card::getName()const
{
	return name;
}
void Card::setEffect(const std::string& effect)
{
	this->effect = effect;
}
std::string Card::getEffect()const
{
	return effect;
}
unsigned int Card::getRarity()const
{
	return rarity;
}
void Card::setRarity(const unsigned int& rarity)
{
	this->rarity = rarity;
}
