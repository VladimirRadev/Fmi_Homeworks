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
#include "Money.hpp"
Money::Money():wallet(0,0){}
Money::Money(const Money& rhs)
{
	this->wallet.first = rhs.wallet.first;
	this->wallet.second = rhs.wallet.second;

}
void Money::addMoney(const unsigned int& gold, const unsigned int& silver)
{
	int newGold = this->wallet.first, newSilver = this->wallet.second;
	newSilver += silver;
	newGold += gold;
	if (newSilver >= 100)
	{
		newGold += (int)(newSilver / 100);
		newSilver = newSilver % 100;
		this->wallet.first = newGold;
		this->wallet.second = newSilver;
		return;
	}
	else
	{
		this->wallet.first = newGold;
		this->wallet.second = newSilver;
		return;
	}
}
void Money::removeMoney(const unsigned int& gold, const unsigned int& silver)
{
	int newGold = this->wallet.first, newSilver = this->wallet.second;
	newGold -= gold;
	if (newGold < 0)
	{
		std::cout << "Not so much avalaible money to distract!" << std::endl;
		return;
	}
	else if (newGold == 0)
	{
		if ((int)(newSilver - silver )< 0)
		{
			std::cout << "Not so much avalaible money to distract!" << std::endl;
			return;
		}
		else if ((int)(newSilver - silver) == 0)
		{
			this->wallet.first = 0;
			this->wallet.second = 0;
			return;
		}
		else
		{
			newSilver -= silver;
			this->wallet.first = 0;
			this->wallet.second = newSilver;
			return;
		}
	}
	else
	{
		int currentSilver = silver;
		while (currentSilver > 0)
		{
			if (newSilver == 0)
			{
				newGold -= 1;
				newSilver = 100;
			}

			--newSilver;
			--currentSilver;
		}
		if (newGold < 0 || newSilver < 0)
		{
			std::cout << "Not so much avalaible money to distract!" << std::endl;
			return;
		}
		else
		{
			this->wallet.first = newGold;
			this->wallet.second = newSilver;
			return;
		}
	}
	
}
void Money::clearMoney()
{
	this->wallet.first = 0;
	this->wallet.second = 0;
	return;
}
const unsigned int Money::getGold()const
{
	return this->wallet.first;
}
const unsigned int Money::getSilver()const
{
	return this->wallet.second;

}