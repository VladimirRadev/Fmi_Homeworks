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
#include "Duelist.hpp"
Duelist::Duelist(const std::string& name) :name(name) {}
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
		outFile << deck;
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
		inFile >> this->deck;
	}
	else
	{
		return false;
	}
	inFile.close();
	return true;
}
void Duelist::duel(Duelist& oponenent)
{
	if (this->deck.getCardsCount() != oponenent.getDeck().getCardsCount())
	{
		std::cout << "Battle between duelist: " << this->name << " and duelist: " << oponenent.name << " is impossible! Different cards count in their decks" << std::endl;
		return;
	}
	else if ((this->deck.getCardsCount() == 0) && (oponenent.getDeck().getCardsCount() == 0))
	{
		std::cout << "No available cards in decks of duelists: " << this->name << " and " << oponenent.name << std::endl;
		return;
	}
	else
	{
		this->deck.shuffle();
		oponenent.getDeck().shuffle();

		int oponent1Points = 0,oponent2Points=0;
		for (int i = 0; i < this->deck.getCards().size(); i++)
		{
			if (*(this->deck.getCards()[i]) < *(oponenent.getDeck().getCards()[i]))
			{
				oponent2Points++;
				continue;
			}
			else if (*(this->deck.getCards()[i]) > *(oponenent.getDeck().getCards()[i]))
			{
				oponent1Points++;
				continue;
			}
			//equal rarity
			else
			{
				continue;
			}
		}
		if (oponent1Points > oponent2Points)
		{
			std::cout << "Duelist with name: " << this->name <<" points ["<<oponent1Points<< "] won the battle against duelist with name: " 
				<< oponenent.name << " points [" << oponent2Points << "]"<< std::endl;
			return;
		}
		else if (oponent1Points < oponent2Points)
		{
			std::cout << "Duelist with name: " << oponenent.name << " points [" << oponent2Points << "] won the battle against duelist with name: "
				<< this->name << " points [" << oponent1Points << "]" << std::endl;
			return;
		}
		else
		{
			std::cout << "Battle between duelist with name: " << this->name << " and duelist with name: " << oponenent.name << " finished with tied" 
				<<"["<<oponent1Points<<"]"<<" : "<<"["<<oponent2Points<<"]"<<std::endl;
			return;
		}
	}
}
void duel(Duelist& oponent1, Duelist& oponent2)
{
	if (oponent1.getDeck().getCardsCount() != oponent2.getDeck().getCardsCount())
	{
		std::cout << "Battle between duelist: " << oponent1.name << " and duelist: " << oponent2.name << " is impossible! Different cards count in their decks" << std::endl;
		return;
	}
	else if ((oponent1.getDeck().getCardsCount() == 0) && (oponent2.getDeck().getCardsCount() == 0))
	{
		std::cout << "No available cards in decks of duelists: " << oponent1.name << " and " << oponent2.name << std::endl;
		return;
	}
	else
	{
		oponent1.getDeck().shuffle();
		oponent2.getDeck().shuffle();

		int oponent1Points = 0, oponent2Points = 0;
		for (int i = 0; i < oponent1.getDeck().getCards().size(); i++)
		{
			if (*(oponent1.getDeck().getCards()[i]) < *(oponent2.getDeck().getCards()[i]))
			{
				oponent2Points++;
				continue;
			}
			else if (*(oponent1.getDeck().getCards()[i]) > *(oponent2.getDeck().getCards()[i]))
			{
				oponent1Points++;
				continue;
			}
			//equal rarity
			else
			{
				continue;
			}
		}
		if (oponent1Points > oponent2Points)
		{
			std::cout << "Duelist with name: " << oponent1.name << " points [" << oponent1Points << "] won the battle against duelist with name: "
				<< oponent2.name << " points [" << oponent2Points << "]" << std::endl;
			return;
		}
		else if (oponent1Points < oponent2Points)
		{
			std::cout << "Duelist with name: " << oponent2.name << " points [" << oponent2Points << "] won the battle against duelist with name: "
				<< oponent1.name << " points [" << oponent1Points << "]" << std::endl;
			return;
		}
		else
		{
			std::cout << "Battle between duelist with name: " << oponent1.name << " and duelist with name: " << oponent2.name << " finished with tied"
				<< "[" << oponent1Points << "]" << " : " << "[" << oponent2Points << "]" << std::endl;
			return;
		}
	}

}
