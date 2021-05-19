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
#pragma once
#include "Card.hpp"
#include <iostream>
#include <string>

enum class CardType
{
	TRAP,
	BUFF,
	SPELL
};

class MagicCard :virtual public Card
{
private:
	CardType type;
public:
	MagicCard(const std::string& name = "", const std::string effect = "",const unsigned int& rarity=0,
		const CardType& type = CardType::TRAP);
	~MagicCard() = default;
	void setType(const CardType& type);
	CardType getType()const;
	const std::string getTypeAsString()const;
	bool operator<(const Card& rhs)override;
	bool operator>(const Card& rhs)override;
	Card* clone()const override;
	void print()const override;
};
