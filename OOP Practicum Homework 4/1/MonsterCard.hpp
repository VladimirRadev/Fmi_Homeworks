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
#include <string>
#include <iostream>
class MonsterCard :virtual public Card
{
private:
	unsigned int attackPoints;
	unsigned int defencePoints;
public:
	MonsterCard(const std::string& name = "", const std::string& effect = "",const unsigned int& rarity=0,
		const unsigned int& attackPoints = 0, const unsigned int& defencepoints = 0);
	~MonsterCard() = default;
	void setAttackPoints(const unsigned int& inputAttackPoints);
	unsigned int getAttackPoints()const;
	void setDefencePoints(const unsigned int& inputDefencePoints);
	unsigned int getDefencePoints()const;
	bool operator<(const Card& rhs)override;
	bool operator>(const Card& rhs)override;
	Card* clone()const override;
	void print()const override;
};
