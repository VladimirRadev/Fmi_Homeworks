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
#include "MagicCard.hpp"
MagicCard::MagicCard(const std::string& name, const std::string effect, const unsigned int& rarity,
	const CardType& type):Card(name, effect,rarity)
{
	this->setType(type);
}
void MagicCard::setType(const CardType& type)
{
	this->type = type;
}
CardType MagicCard::getType()const
{
	return type;
}
const std::string MagicCard::getTypeAsString()const
{
	if (type == CardType::TRAP)
	{
		return "TRAP";
	}
	else if (type == CardType::BUFF)
	{
		return "BUFF";
	}
	else if (type == CardType::SPELL)
	{
		return "SPELL";
	}
	else
	{
		return "";
	}


}
bool MagicCard::operator<(const Card& rhs)
{
	return (this->getRarity() < rhs.getRarity());
}
bool MagicCard::operator>(const Card& rhs)
{
	return (this->getRarity() > rhs.getRarity());
}
Card* MagicCard::clone()const
{
	return new MagicCard(*this);
}
void MagicCard::print()const
{
	std::cout << "Magic card with name: " << this->getName() << " and effect: "
		<< this->getEffect() <<", with rarity:  "<<this->getRarity()<<" and type: " << this->getTypeAsString() << std::endl;
}