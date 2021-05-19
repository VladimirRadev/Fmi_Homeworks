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

#include <string>
class Card
{
private:
	std::string name;
	std::string effect;	
	unsigned int rarity;
public:
	Card(const std::string& name = "", const std::string& effect = "",const unsigned int& rarity=0);
	virtual ~Card() = default;
	void setName(const std::string& name);
	std::string getName()const;
	void setEffect(const std::string& effect);
	std::string getEffect()const;
	unsigned int getRarity()const;
	void setRarity(const unsigned int& rarity);
	virtual bool operator<(const Card& rhs)=0;
	virtual bool operator>(const Card& rhs)=0;
	virtual Card* clone()const = 0;
	virtual void print()const = 0;
};
