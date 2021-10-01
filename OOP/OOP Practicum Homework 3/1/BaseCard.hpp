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
class BaseCard
{
private:
	std::string name;
	std::string effect;
public:
	BaseCard(const std::string& name = "", const std::string& effect = "");
    void setName(const std::string& name);
	std::string getName()const;
	void setEffect(const std::string& effect);
	std::string getEffect()const;
	virtual void print()const = 0;
};