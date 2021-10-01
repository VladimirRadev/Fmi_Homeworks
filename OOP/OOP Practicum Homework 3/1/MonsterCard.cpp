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
#include "MonsterCard.hpp"
MonsterCard::MonsterCard(const std::string& name, const std::string& effect, const int& attackPoints, const int& defencepoints)
	:BaseCard(name, effect)
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
	return this->attackPoints;
}
void MonsterCard::setDefencePoints(const unsigned int& inputDefencePoints)
{
	this->defencePoints = inputDefencePoints;
}
unsigned int MonsterCard::getDefencePoints()const
{
	return this->defencePoints;
}
void MonsterCard::print()const
{
	std::cout << "Monster card with name: " << this->getName() << " and effect: "
		<< this->getEffect() << " with attack points: " << this->getAttackPoints()<<" with defence points: "
		<<this->getDefencePoints()<< std::endl;
}