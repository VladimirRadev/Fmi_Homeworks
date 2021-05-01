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
#include "PendulumCard.hpp"
PendulumCard::PendulumCard(const std::string& name, const std::string effect, const unsigned int& attackPoints,
	const unsigned int defencePoints, const unsigned int& pendulumScale, const CardType& type)
	:BaseCard(name,effect),MonsterCard(name,effect,attackPoints,defencePoints),MagicCard(name,effect,type)
	
{
	this->setPendulumScale(pendulumScale);
}
void PendulumCard::setPendulumScale(const unsigned int& scale)
{
	if (scale < 1 || scale>13)
	{
		std::cout << "Pendilum scale must be within [1,13] range! " << std::endl;
		return;
	}
	else
	{
		this->pendulumScale = scale;
	}
}
unsigned int PendulumCard::getPendelumScale()const
{
	return this->pendulumScale;
}
void PendulumCard::print()const
{
	std::cout << "PendulumCard with name: " << this->getName() << " and effect: " << this->getEffect() << std::endl;
	std::cout << "From monster card items: " << this->getAttackPoints() << " attack points, " << this->getDefencePoints() << " defence points." << std::endl;
	std::cout << "From magic card items: " << this->getTypeAsString() << " card type." << std::endl;
	std::cout << "With Pendulum scale: [" << this->getPendelumScale() << "] \n";
}