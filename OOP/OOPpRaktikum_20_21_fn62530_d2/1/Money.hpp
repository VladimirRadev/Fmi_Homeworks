/**
* Solution to homework assignment 2
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
#include <vector>
#include <utility>
class Money
{
private:
	//gold, silver
	std::pair<unsigned int, unsigned int>wallet;
public:
	Money();
	Money(const Money& rhs);
	void addMoney(const unsigned int& gold, const unsigned int& silver);
	void removeMoney(const unsigned int& gold, const unsigned int& silver);
	void clearMoney();
	const unsigned int getGold()const;
	const unsigned int getSilver()const;
};