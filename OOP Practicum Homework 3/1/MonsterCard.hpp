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
#include <string>
#include "BaseCard.hpp"
#include <iostream>
class MonsterCard:virtual public BaseCard
{
private:
	unsigned int attackPoints;
	unsigned int defencePoints;
public:
	MonsterCard(const std::string& name="",const std::string& effect="",const int& attackPoints=0, const int& defencepoints=0);
	void setAttackPoints(const unsigned int& inputAttackPoints);
	unsigned int getAttackPoints()const;
	void setDefencePoints(const unsigned int& inputDefencePoints);
	unsigned int getDefencePoints()const;
	void print()const override;
};
