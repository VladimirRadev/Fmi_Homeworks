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
#include <iostream>
#include <string>
#include "MagicCard.hpp"
#include "MonsterCard.hpp"
#include "Card.hpp"
class PendelumCard : public MonsterCard, public MagicCard
{
private:
	unsigned int pendelumScale = 1;
public:
	PendelumCard(const std::string& name="", const std::string effect = "", const unsigned int& rarity = 0,
		const unsigned int& attackPoints = 0,const unsigned int& defencePoints = 0,
		const unsigned int& pendulumScale = 1, const CardType& type = CardType::TRAP);
	~PendelumCard() = default;
	void setPendulumScale(const unsigned int& scale);
	unsigned int getPendelumScale()const;
	bool operator<(const Card& rhs)override;
	bool operator>(const Card& rhs)override;
	Card* clone()const override;
	void print()const override;
};
