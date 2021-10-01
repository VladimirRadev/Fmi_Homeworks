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
#include "Deck.hpp"
Deck::Deck(const std::string& name) :name(name) {}
Deck::Deck(const Deck& rhs)
{
	this->name = rhs.name;
	for (auto x : rhs.cards)
	{
		this->cards.push_back(x->clone());
	}
}
Deck& Deck::operator=(const Deck& rhs)
{
	if (this != &rhs)
	{
		this->name = rhs.name;
		for (auto x : this->cards)
		{
			delete x;
		}
		this->cards.clear();

		for (auto x : rhs.cards)
		{
			this->cards.push_back(x->clone());
		}
	}
	return *this;
}
Deck::~Deck()
{
	for (auto x : this->cards)
	{
		delete x;
	}
	this->cards.clear();
}
void Deck::setDeckName(const std::string& name)
{
	this->name = name;
}
std::string Deck::getDeckName()const
{
	return name;
}
const std::vector<Card*>& Deck::getCards()const
{
	return cards;
}
int Deck::getMonsterCardsCount()const
{
	int rezult = 0;
	for (int i = 0; i < cards.size(); i++)
	{
		PendelumCard* checkWetherIsPendelumCard = dynamic_cast<PendelumCard*>(cards[i]);
		if (checkWetherIsPendelumCard != nullptr)
		{
			continue;
		}
		MonsterCard* ptr = dynamic_cast<MonsterCard*>(cards[i]);
		if (ptr != nullptr)
		{
			++rezult;
			continue;
		}
		else
		{
			continue;
		}
	}
	return rezult;
}
int Deck::getMagicCardsCount()const
{
	int rezult = 0;
	for (int i = 0; i < cards.size(); i++)
	{
		PendelumCard* checkWetherIsPendelumCard = dynamic_cast<PendelumCard*>(cards[i]);
		if (checkWetherIsPendelumCard != nullptr)
		{
			continue;
		}
		MagicCard* ptr = dynamic_cast<MagicCard*>(cards[i]);
		if (ptr != nullptr)
		{
			++rezult;
			continue;
		}
		else
		{
			continue;
		}
	}
	return rezult;
}
int Deck::getPendulumCardsCount()const
{
	int rezult = 0;
	for (int i = 0; i < cards.size(); i++)
	{
		PendelumCard* ptr = dynamic_cast<PendelumCard*>(cards[i]);
		if (ptr != nullptr)
		{
			++rezult;
			continue;
		}
		else
		{
			continue;
		}
	}
	return rezult;

}
int Deck::getCardsCount()const
{
	return cards.size();
}
void Deck::addCard(Card* cardToAdd)
{
	// the outside world should care about deleting dynamic memory, here we make a dynamic copy of given item
	this->cards.push_back(cardToAdd->clone());
}
void Deck::setCard(const unsigned int& index, Card* newCard)
{
	if (index < 0 || index >= this->cards.size())
	{
		std::cout << "Invalid given index. There is no element on this index! " << std::endl;
		return;
	}
	//check whether card on given index and given card as argument are both PendelumCard
	PendelumCard* ifActualIsPendelum = dynamic_cast<PendelumCard*>(this->cards[index]);
	PendelumCard* ifGivenIsPendelum = dynamic_cast<PendelumCard*>(newCard);
	if ((ifActualIsPendelum != nullptr && ifGivenIsPendelum == nullptr)
		|| (ifActualIsPendelum == nullptr && ifGivenIsPendelum != nullptr))
	{
		std::cout << "Given card is not with same type as actual card on this index. It must be same" << std::endl;
		return;
	}
	else if (ifActualIsPendelum != nullptr && ifGivenIsPendelum != nullptr)
	{
		delete this->cards[index];
		this->cards[index] = newCard->clone();
		return;
	}
	else if (ifActualIsPendelum == nullptr && ifGivenIsPendelum == nullptr)
	{

		//check whether card on given index and given card as argument are both MonsterCard
		MonsterCard* ifActualIsMonster = dynamic_cast<MonsterCard*>(this->cards[index]);
		MonsterCard* ifGivenIsMonster = dynamic_cast<MonsterCard*>(newCard);
		if (ifActualIsMonster != nullptr && ifGivenIsMonster != nullptr)
		{
			delete this->cards[index];
			this->cards[index] = newCard->clone();
			return;
		}

		//check whether card on given index and given card as argument are both MagicCard
		MagicCard* ifActualIsMagic = dynamic_cast<MagicCard*>(this->cards[index]);
		MagicCard* ifGivenIsMagic = dynamic_cast<MagicCard*>(newCard);
		if (ifActualIsMagic != nullptr && ifGivenIsMagic != nullptr)
		{
			delete this->cards[index];
			this->cards[index] = newCard->clone();
			return;
		}


		//if we are here it means that given card as argument is not same type as actual-> Error message

		std::cout << "Given card is not with same type as actual card on this index. It must be same" << std::endl;
	}
}
void Deck::clearDeck()
{
	if (this->cards.empty())
	{
		return;
	}
	else
	{
		int indexToDelete = this->cards.size() - 1;
		while (!this->cards.empty())
		{
			delete this->cards[indexToDelete];
			this->cards.erase(this->cards.begin()+indexToDelete);
			--indexToDelete;
		}
	}
}
void Deck::shuffle()
{
	if (this->cards.size() > 0)
	{
		auto rng = std::default_random_engine{};
		std::shuffle(std::begin(this->cards), std::end(this->cards), rng);
	}

}
std::ostream& operator<<(std::ostream& outFile, const Deck& deck)
{
	outFile << deck.getDeckName() << '|' << deck.getCardsCount() << '|' << deck.getMonsterCardsCount()
		<< '|' << deck.getMagicCardsCount()
		<< '|' << deck.getPendulumCardsCount() << '\n';

	//monsterCards
	for (int i = 0; i < deck.getCardsCount(); i++)
	{
		PendelumCard* isCurrentPendelumCard = dynamic_cast<PendelumCard*>(deck.getCards()[i]);
		if (isCurrentPendelumCard != nullptr)
		{
			continue;
		}
		else
		{
			MonsterCard* isCurrentMonsterCard = dynamic_cast<MonsterCard*>(deck.getCards()[i]);
			if (isCurrentMonsterCard != nullptr)
			{
				outFile << isCurrentMonsterCard->getName() << '|' << isCurrentMonsterCard->getEffect()
					<< '|' << isCurrentMonsterCard->getRarity() << '|' << isCurrentMonsterCard->getAttackPoints()
					<< '|' << isCurrentMonsterCard->getDefencePoints() << '\n';

			}
			else
			{
				continue;
			}
		}
	}
	//magicCards
	for (int i = 0; i < deck.getCardsCount(); i++)
	{
		PendelumCard* isCurrentPendelumCard = dynamic_cast<PendelumCard*>(deck.getCards()[i]);
		if (isCurrentPendelumCard != nullptr)
		{
			continue;
		}
		else
		{
			MagicCard* isCurrentMagicCard = dynamic_cast<MagicCard*>(deck.getCards()[i]);
			if (isCurrentMagicCard != nullptr)
			{
				outFile << isCurrentMagicCard->getName() << '|' << isCurrentMagicCard->getEffect()
					<< '|' << isCurrentMagicCard->getRarity() << '|' << isCurrentMagicCard->getTypeAsString() << '\n';

			}
			else
			{
				continue;
			}
		}
	}
	//pendelum cards
	for (int i = 0; i < deck.getCardsCount(); i++)
	{
		PendelumCard* isCurrentPendelumCard = dynamic_cast<PendelumCard*>(deck.getCards()[i]);
		if (isCurrentPendelumCard != nullptr)
		{
			outFile << isCurrentPendelumCard->getName() << '|' << isCurrentPendelumCard->getEffect()
				<< '|' << isCurrentPendelumCard->getRarity() << '|' << isCurrentPendelumCard->getAttackPoints() << '|'
				<< isCurrentPendelumCard->getDefencePoints() << '|' << isCurrentPendelumCard->getPendelumScale() << '|'
				<< isCurrentPendelumCard->getTypeAsString() << '\n';
		}
		else
		{
			continue;
		}
	}
	return outFile;
}
std::istream& operator>>(std::istream& inFile, Deck& deck)
{
	deck.clearDeck();

	std::string newDeckName;
	int newCardsCount = 0;
	int newMonsterCardCount = 0;
	int newMagicCardCount = 0;
	int newPendelumCardCount = 0;

	std::getline(inFile, newDeckName, '|');
	inFile >> newCardsCount;
	inFile.ignore();
	inFile >> newMonsterCardCount;
	inFile.ignore();
	inFile >> newMagicCardCount;
	inFile.ignore();
	inFile >> newPendelumCardCount;
	inFile.ignore();
	deck.setDeckName(newDeckName);
	for (int i = 0; i < newMonsterCardCount; i++)
	{
		std::string name;
		std::string effect;
		int rarity = 0;
		int attackPoints = 0;
		int defencePoints = 0;

		std::getline(inFile, name, '|');
		std::getline(inFile, effect, '|');
		inFile >> rarity;
		inFile.ignore();
		inFile >> attackPoints;
		inFile.ignore();
		inFile >> defencePoints;
		Card* toAdd = new MonsterCard(name, effect, rarity, attackPoints, defencePoints);
		deck.addCard(toAdd);
		delete toAdd;
	}
	for (int i = 0; i < newMagicCardCount; i++)
	{
		std::string name;
		std::string effect;
		int rarity = 0;
		std::string type;

		std::getline(inFile, name, '|');
		std::getline(inFile, effect, '|');
		inFile >> rarity;
		inFile.ignore();
		std::getline(inFile, type, '\n');
		if (type == "TRAP")
		{
			Card* toAdd=new MagicCard(name, effect, rarity, CardType::TRAP);
			deck.addCard(toAdd);
			delete toAdd;
		}
		else if (type == "BUFF")
		{
			Card* toAdd = new MagicCard(name, effect, rarity, CardType::BUFF);
			deck.addCard(toAdd);
			delete toAdd;
		}
		else if (type == "SPELL")
		{
			Card* toAdd = new MagicCard(name, effect, rarity, CardType::SPELL);
			deck.addCard(toAdd);
			delete toAdd;
		}

		else
		{
			//wrong input. Nothing to add!
		}
	}
	for (int i = 0; i < newPendelumCardCount; i++)
	{
		std::string name;
		std::string effect;
		int rarity = 0;
		int attackPoints = 0;
		int defencePoints = 0;
		int pendulumScale = 0;
		std::string type;

		std::getline(inFile, name, '|');
		std::getline(inFile, effect, '|');
		inFile >> rarity;
		inFile.ignore();
		inFile >> attackPoints;
		inFile.ignore();
		inFile >> defencePoints;
		inFile.ignore();
		inFile >> pendulumScale;
		inFile.ignore();
		std::getline(inFile, type, '\n');
		if (type == "TRAP")
		{
			Card* toAdd = new PendelumCard(name, effect, rarity, attackPoints, defencePoints, pendulumScale, CardType::TRAP);
			deck.addCard(toAdd);
			delete toAdd;
		}
		else if (type == "BUFF")
		{
			Card* toAdd = new PendelumCard(name, effect, rarity, attackPoints, defencePoints, pendulumScale, CardType::BUFF);
			deck.addCard(toAdd);
			delete toAdd;

		}
		else if (type == "SPELL")
		{
			Card* toAdd = new PendelumCard(name, effect, rarity, attackPoints, defencePoints, pendulumScale, CardType::SPELL);
			deck.addCard(toAdd);
			delete toAdd;
		}

		else
		{
			//wrong input. Nothing to add!
		}
	}
	return inFile;
}