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
#include "PendelumCard.hpp"
PendelumCard::PendelumCard(const std::string& name,const std::string effect,const unsigned int& rarity,
	const unsigned int& attackPoints,const unsigned int& defencePoints,
	const unsigned int& pendelumScale,const CardType& type):
	Card(name,effect,rarity),MonsterCard(name,effect,rarity,attackPoints,defencePoints),MagicCard(name,effect,rarity,type)
{
	this->pendelumScale = pendelumScale;
}
void PendelumCard::setPendulumScale(const unsigned int& scale)
{
	this->pendelumScale = scale;
}
unsigned int PendelumCard::getPendelumScale()const
{
	return pendelumScale;
}
bool PendelumCard::operator<(const Card& rhs)
{
	return (this->getRarity() < rhs.getRarity());
}
bool PendelumCard::operator>(const Card& rhs)
{
	return (this->getRarity() > rhs.getRarity());
}
Card* PendelumCard::clone()const 
{
	return new PendelumCard(*this);
}
void PendelumCard::print()const
{
	std::cout << "PendulumCard with name: " << this->getName() << " and effect: " << this->getEffect() <<" , and rarity: "<<this->getRarity()<<std::endl;
	std::cout << "From monster card items: " << this->getAttackPoints() << " attack points, " << this->getDefencePoints() << " defence points." << std::endl;
	std::cout << "From magic card items: " << this->getTypeAsString() << " card type." << std::endl;
	std::cout << "With Pendulum scale: [" << this->getPendelumScale() << "] \n";
}

