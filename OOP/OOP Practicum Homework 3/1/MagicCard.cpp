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
#include "MagicCard.hpp"
MagicCard::MagicCard(const std::string& name, const std::string effect, const CardType& type)
	:BaseCard(name, effect)
{
	this->setType(type);
}
void MagicCard::setType(const CardType& type)
{
	this->type = type;
}
CardType MagicCard::getType()const
{
	return this->type;
}
const std::string MagicCard::getTypeAsString()const
{
	if (this->type == CardType::TRAP)
	{
		return "TRAP";
	}
	else if (this->type == CardType::BUFF)
	{
		return "BUFF";
	}
	else if (this->type == CardType::SPELL)
	{
		return "SPELL";
	}
	else
	{
		return "";
	}


}
void MagicCard::print()const
{
	std::cout << "Magic card with name: " << this->getName() << " and effect: " 
		<< this->getEffect() << " and type: " << this->getTypeAsString() << std::endl;
}