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
#include "Deck.hpp"
#include <iostream>
#include <fstream>
#include <string>
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
	void display()const;

};
