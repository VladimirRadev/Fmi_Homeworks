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
#include <string>
#include <iostream>
#include "MagicCard.hpp"
#include "MonsterCard.hpp"
#include "Deck.hpp"
#include "Duelist.hpp"
int main()
{
	MonsterCard dragon("Blue-Eyes White Dragon", "This legendary dragon is a powerful engine of destruction.", 3000, 2500);
	MonsterCard magician("Dark Magician", "The ultimate wizard.", 2500, 2100);
	MagicCard swords("Swords of Revealing Light", "Your opponent's monsters cannot declare an attack.", CardType::SPELL);
	MagicCard cylinder("Magic Cylinder", "Inflict damage to your opponent equal to its ATK.", CardType::TRAP);
	PendulumCard timegazer("Timegazer Magician", "Your opponent cannot activate Trap Magic Cards.", 1200, 600, 8,CardType::TRAP);
	PendulumCard clutchHelper("Clutch Helper", "Your opponent cannot activate BUFF Magic Cards.", 5200, 6372, 13, CardType::BUFF);
	PendulumCard divaMech("Dva operating", "You slow enemy's speed! ", 3245, 1930, 3, CardType::SPELL);
	Duelist firstDuelist("Ivan Ivanov");
	firstDuelist.getDeck().setDeckname("Magician Deck");
	firstDuelist.getDeck().addMonsterCard(dragon);
	firstDuelist.getDeck().addMonsterCard(magician);
	firstDuelist.getDeck().addMagicCard(swords);
	firstDuelist.getDeck().addMagicCard(cylinder);
	firstDuelist.getDeck().addPendulumCard(timegazer);
	MagicCard box("Mystic Box", "Destroy one monster.", CardType::SPELL);
	firstDuelist.getDeck().setMagicCard(0, box);
	firstDuelist.display();
	firstDuelist.saveDeck("magican_deck.txt");
	firstDuelist.loadDeck("magican_deck.txt");
	std::cout << "\n|||||||||||||||||||||||||Must be equal as down (down arrow)||||||||||||||||||||||||||| \n\n";
	firstDuelist.display();


	std::cout << "\n*******************************End of first example********************* \n\n";

	Duelist secondDuelist("Tosho Kukata");
	secondDuelist.getDeck().setDeckname("Thug deck");
	secondDuelist.getDeck().addMonsterCard(dragon);
	secondDuelist.getDeck().addMagicCard(cylinder);
	secondDuelist.getDeck().addMagicCard(box);
	secondDuelist.getDeck().addPendulumCard(clutchHelper);
	secondDuelist.getDeck().addPendulumCard(divaMech);
	PendulumCard newPendelumCard("OK.Lets'go! Enemy spotted!", "Your aim is weak! ", 1914, 1948, 7, CardType::BUFF);
	secondDuelist.getDeck().setPendulumCard(0, newPendelumCard);
	secondDuelist.display();
	//info of secondDuelist must be save in thug_deck txt file
	secondDuelist.saveDeck("thug_deck.txt");

	std::cout << "\n*******************************End of second example********************* \n\n";

	Duelist thirdDuelist("Glavniq Iliev");
	thirdDuelist.loadDeck("dwarf_deck.txt");
	//info of third duelist must be same as info stored in dwarf_deck txt file
	thirdDuelist.display();

	std::cout << "\n*******************************End of third example********************* \n\n";



	return 0;
}