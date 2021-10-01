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
#pragma once
#include "BaseCard.hpp"
#include <iostream>
#include <string>

enum class CardType
{
	TRAP,
	BUFF,
	SPELL
};

class MagicCard :virtual public BaseCard
{
private:
	CardType type;
public:
	MagicCard(const std::string& name = "", const std::string effect = "", const CardType& type = CardType::TRAP);
	void setType(const CardType& type);
	CardType getType()const;
	const std::string getTypeAsString()const;
	void print()const override;
};