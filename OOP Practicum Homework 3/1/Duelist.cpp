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
#include "Duelist.hpp"
#include <iostream>
Duelist::Duelist(const std::string& name)
{
	this->name = name;
}
Deck& Duelist::getDeck()
{
	return this->deck;
}
bool Duelist::saveDeck(const char* fileName)const
{
	std::ofstream outFile;
	outFile.open(fileName, std::ios::out);
	if (outFile)
	{
		outFile << this->deck.getDeckName() << '|' << this->deck.getMonsterCardsCount()
			<< '|' << this->deck.getMagicCardsCount()
			<< '|' << this->deck.getPendulumCardsCount() << '\n';
		for (int i = 0; i < this->deck.getMonsterCardsCount(); i++)
		{
			outFile << this->deck.getMonsterCardsPtr()[i].getName() << '|'
				<< this->deck.getMonsterCardsPtr()[i].getEffect() << '|'
				<< this->deck.getMonsterCardsPtr()[i].getAttackPoints() << '|'
				<< this->deck.getMonsterCardsPtr()[i].getDefencePoints() << '\n';
		}
		for (int i = 0; i < this->deck.getMagicCardsCount(); i++)
		{
			outFile << this->deck.getMagicCardsPtr()[i].getName() << '|'
				<< this->deck.getMagicCardsPtr()[i].getEffect() << '|'
				<< this->deck.getMagicCardsPtr()[i].getTypeAsString() << '\n';
		}
		for (int i = 0; i < this->deck.getPendulumCardsCount(); i++)
		{
			outFile << this->deck.getPendulumCardsPtr()[i].getName() << '|'
				<< this->deck.getPendulumCardsPtr()[i].getEffect() << '|'
				<< this->deck.getPendulumCardsPtr()[i].getAttackPoints() << '|'
				<< this->deck.getPendulumCardsPtr()[i].getDefencePoints()<<'|'
				<<this->deck.getPendulumCardsPtr()[i].getPendelumScale()<<'|'
				<<this->deck.getPendulumCardsPtr()[i].getTypeAsString()<<'\n';
		}
	}
	else
	{
		return false;
	}
	outFile.close();
	return true;

}
bool Duelist::loadDeck(const char* fileName)
{
	std::ifstream inFile;
	inFile.open(fileName, std::ios::in);
	if (inFile)
	{
		this->deck.clearDeck();

		std::string newDeckName;
		int newMonsterCardCount = 0;
		int newMagicCardCount = 0;
		int newPendelumCardCount = 0;

		std::getline(inFile, newDeckName, '|');
		inFile >> newMonsterCardCount;
		inFile.ignore();
		inFile >> newMagicCardCount;
		inFile.ignore();
		inFile >> newPendelumCardCount;
		this->deck.setDeckname(newDeckName);
		for (int i = 0; i < newMonsterCardCount; i++)
		{
			std::string name;
			std::string effect;
			int attackPoints=0;
			int defencePoints = 0;

			std::getline(inFile, name, '|');
			std::getline(inFile, effect, '|');
			inFile >> attackPoints;
			inFile.ignore();
			inFile >> defencePoints;
			this->deck.addMonsterCard(MonsterCard(name, effect, attackPoints, defencePoints));
		}
		for (int i = 0; i < newMagicCardCount; i++)
		{
			std::string name;
			std::string effect;
			std::string type;

			std::getline(inFile, name, '|');
			std::getline(inFile, effect, '|');
			std::getline(inFile, type, '\n');
			if (type == "TRAP")
			{
				this->deck.addMagicCard(MagicCard(name, effect, CardType::TRAP));
			}
			else if (type == "BUFF")
			{
				this->deck.addMagicCard(MagicCard(name, effect, CardType::BUFF));
			}
			else if (type == "SPELL")
			{
				this->deck.addMagicCard(MagicCard(name, effect, CardType::SPELL));
			}
			
			else
			{
				return false;
			}
		}
		for (int i = 0; i < newPendelumCardCount; i++)
		{
			std::string name;
			std::string effect;
			int attackPoints = 0;
			int defencePoints = 0;
			int pendulumScale = 0;
			std::string type;

			std::getline(inFile, name, '|');
			std::getline(inFile, effect, '|');
			inFile >> attackPoints;
			inFile.ignore();
			inFile >> defencePoints;
			inFile.ignore();
			inFile >> pendulumScale;
			inFile.ignore();
			std::getline(inFile, type, '\n');
			if (type == "TRAP")
			{
				this->deck.addPendulumCard(PendulumCard(name, effect, attackPoints, defencePoints, pendulumScale, CardType::TRAP));
			}
			else if (type == "BUFF")
			{
				this->deck.addPendulumCard(PendulumCard(name, effect, attackPoints, defencePoints, pendulumScale, CardType::BUFF));
			}
			else if (type == "SPELL")
			{
				this->deck.addPendulumCard(PendulumCard(name, effect, attackPoints, defencePoints, pendulumScale, CardType::SPELL));
			}

			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;

	}
	inFile.close();
	return true;
}
void Duelist::display()const
{
	std::cout << "Duelist with name: " << this->name << " has in his deck: "<<this->deck.getDeckName()<< std::endl<<std::endl;
	//monsterCards;
	std::cout << "MonsterCards:"<<std::endl;
	for (int i = 0; i < this->deck.getMonsterCardsPtr().size(); i++)
	{
		std::cout << this->deck.getMonsterCardsPtr()[i].getName()<<' '
			<< this->deck.getMonsterCardsPtr()[i].getEffect() << ' '
			<< this->deck.getMonsterCardsPtr()[i].getAttackPoints() << ' '
			<<this->deck.getMonsterCardsPtr()[i].getDefencePoints()<<std::endl;
	}
	std::cout << std::endl;
	//magicCards
	std::cout << "MagicCards:" << std::endl;
	for (int i = 0; i < this->deck.getMagicCardsPtr().size(); i++)
	{
		std::cout << this->deck.getMagicCardsPtr()[i].getName() << ' '
			<<this->deck.getMagicCardsPtr()[i].getEffect() << ' '
			<<this->deck.getMagicCardsPtr()[i].getTypeAsString()<< std::endl;
	}
	std::cout << std::endl;
	//pendulumCards
	std::cout << "PendelumCards :" << std::endl;
	for (int i = 0; i < this->deck.getPendulumCardsPtr().size(); i++)
	{
		std::cout << this->deck.getPendulumCardsPtr()[i].getName() << ' '
			<< this->deck.getPendulumCardsPtr()[i].getEffect() << ' '
			<< this->deck.getPendulumCardsPtr()[i].getAttackPoints() << ' '
			<< this->deck.getPendulumCardsPtr()[i].getDefencePoints() << ' '
			<<this->deck.getPendulumCardsPtr()[i].getPendelumScale() << ' '
			<< this->deck.getPendulumCardsPtr()[i].getTypeAsString() << std::endl;
	}
	std::cout << std::endl;

}