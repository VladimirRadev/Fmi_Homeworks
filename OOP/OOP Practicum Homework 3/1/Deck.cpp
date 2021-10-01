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
#include "Deck.hpp"
#include <iostream>
Deck::Deck(const std::string& name)
{
	this->setDeckname(name);
}
void Deck::setDeckname(const std::string& newName)
{
	this->name = newName;
}
std::string Deck::getDeckName()const
{
	return this->name;
}
const std::vector<MonsterCard>& Deck::getMonsterCardsPtr()const
{
	return this->monsterCards;
}
const std::vector<MagicCard>& Deck::getMagicCardsPtr()const
{
	return this->magicCards;
}
const std::vector<PendulumCard>& Deck::getPendulumCardsPtr()const
{
	return this->pendulumCards;
}
int Deck::getMonsterCardsCount()const
{
	return this->monsterCards.size();
}
int Deck::getMagicCardsCount()const
{
	return this->magicCards.size();
}
int Deck::getPendulumCardsCount()const
{
	return this->pendulumCards.size();
}
void Deck::addMonsterCard(const MonsterCard& monsterCard)
{
	this->monsterCards.push_back(monsterCard);
}
void Deck::addMagicCard(const MagicCard& magicCard)
{
	this->magicCards.push_back(magicCard);
}
void Deck::addPendulumCard(const PendulumCard& pendulumCard)
{
	this->pendulumCards.push_back(pendulumCard);
}
void Deck::setMonsterCard(const int& index, const MonsterCard& newMonsterCard)
{
	if (index<0 || index>(this->monsterCards.size() - 1))
	{
		std::cout << "Index out of monsterCards bounds in deck with name: " << this->getDeckName() << std::endl;
		return;
	}
	this->monsterCards[index] = newMonsterCard;
}
void Deck::setMagicCard(const int& index, const MagicCard& newMagicCard)
{
	if (index<0 || index>(this->magicCards.size() - 1))
	{
		std::cout << "Index out of magicCards bounds in deck with name: " << this->getDeckName() << std::endl;
		return;
	}
	this->magicCards[index] = newMagicCard;
}
void Deck::setPendulumCard(const int& index, const PendulumCard& newPendulumCard)
{
	if (index<0 || index>(this->pendulumCards.size() - 1))
	{
		std::cout << "Index out of pendulumCards bounds in deck with name: " << this->getDeckName() << std::endl;
		return;
	}
	this->pendulumCards[index] = newPendulumCard;
}
void Deck::clearDeck()
{
	this->magicCards.clear();
	this->monsterCards.clear();
	this->pendulumCards.clear();
}
