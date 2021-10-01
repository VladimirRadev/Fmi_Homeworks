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
#include <iostream>
#include <string>
#include "BaseCard.hpp"
#include "MagicCard.hpp"
#include "MonsterCard.hpp"

class PendulumCard :public MonsterCard, public MagicCard
{
private:
	unsigned int pendulumScale=1;
public:
	PendulumCard(const std::string& name = "", const std::string effect = "", const unsigned int& attackPoints = 0,
		const unsigned int defencePoints = 0, const unsigned int& pendulumScale = 1, const CardType& type = CardType::TRAP);
	void setPendulumScale(const unsigned int& scale);
	unsigned int getPendelumScale()const;
	void print()const override;
};

