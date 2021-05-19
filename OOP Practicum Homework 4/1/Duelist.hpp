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
#include <fstream>
#include <string>
#include "Deck.hpp"
class Duelist
{
private:
	std::string name;
	Deck deck;
public:
	Duelist(const std::string& name = "");
	Deck& getDeck();
	bool saveDeck(const char* fileName)const;
	bool loadDeck(const char* fileName);
	void duel(Duelist& openent);
	friend void duel(Duelist& oponent1, Duelist& openent2);
};
