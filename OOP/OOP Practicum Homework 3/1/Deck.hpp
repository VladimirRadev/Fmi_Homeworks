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
#include <vector>
#include "MagicCard.hpp"
#include "MonsterCard.hpp"
#include "PendulumCard.hpp"

class Deck
{
private:
	std::string name;
	std::vector<MonsterCard>monsterCards;
	std::vector<MagicCard>magicCards;
	std::vector<PendulumCard>pendulumCards;
public:
	Deck(const std::string& name = "");
	void setDeckname(const std::string& newName);
	std::string getDeckName()const;
	const std::vector<MonsterCard>& getMonsterCardsPtr()const;
	const std::vector<MagicCard>& getMagicCardsPtr()const;
	const std::vector<PendulumCard>& getPendulumCardsPtr()const;
	int getMonsterCardsCount()const;
	int getMagicCardsCount()const;
	int getPendulumCardsCount()const;
	void addMonsterCard(const MonsterCard& monsterCard);
	void addMagicCard(const MagicCard& magicCard);
	void addPendulumCard(const PendulumCard& pendulumCard);
	void setMonsterCard(const int& index, const MonsterCard& newMonsterCard);
	void setMagicCard(const int& index, const MagicCard& newMagicCard);
	void setPendulumCard(const int& index, const PendulumCard& newPendulumCard);
	void clearDeck();



};
