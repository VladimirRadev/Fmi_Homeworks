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
#include "MonsterCard.hpp"
MonsterCard::MonsterCard(const std::string& name, const std::string& effect, const unsigned int& rarity,
	const unsigned int& attackPoints, const unsigned int& defencepoints) :Card(name, effect, rarity)
{
	this->setAttackPoints(attackPoints);
	this->setDefencePoints(defencepoints);
}
void MonsterCard::setAttackPoints(const unsigned int& inputAttackPoints)
{
	this->attackPoints = inputAttackPoints;
}
unsigned int MonsterCard::getAttackPoints()const
{
	return attackPoints;
}
void MonsterCard::setDefencePoints(const unsigned int& inputDefencePoints)
{
	this->defencePoints = inputDefencePoints;
}
unsigned int MonsterCard::getDefencePoints()const
{
	return defencePoints;
}
bool MonsterCard::operator<(const Card& rhs)
{
	return (this->getRarity() < rhs.getRarity());
}
bool MonsterCard::operator>(const Card& rhs)
{
	return (this->getRarity() > rhs.getRarity());
}
Card* MonsterCard::clone()const
{
	return new MonsterCard(*this);
}
void MonsterCard::print()const
{
	std::cout << "Monster card with name: " << this->getName() << " and effect: "
		<< this->getEffect() <<"with rarity: "<<this->getRarity()<<",with attack points: " << this->getAttackPoints() << " with defence points: "
		<< this->getDefencePoints() << std::endl;
}