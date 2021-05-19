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
#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include "Card.hpp"
#include "MonsterCard.hpp"
#include "MagicCard.hpp"
#include "PendelumCard.hpp"

class Deck
{
private:
	std::string name;
	std::vector<Card*>cards;
public:
	Deck(const std::string& name = "");
	Deck(const Deck& rhs);
	Deck& operator=(const Deck& rhs);
	~Deck();
	void setDeckName(const std::string& name);
	std::string getDeckName()const;
	const std::vector<Card*>& getCards()const;
	int getMonsterCardsCount()const;
	int getMagicCardsCount()const;
	int getPendulumCardsCount()const;
	int getCardsCount()const;
	void addCard(Card* cardToAdd);
	void setCard(const unsigned int& index, Card* newCard);
	void clearDeck();
	void shuffle();
	friend std::ostream& operator<<(std::ostream& out, const Deck& deck);
	friend std::istream& operator>>(std::istream& in, Deck& deck);

};
