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
#include <iostream>
#include "Card.hpp"
#include "MagicCard.hpp"
#include "MonsterCard.hpp"
#include "PendelumCard.hpp"
#include "Deck.hpp"
#include "Duelist.hpp"
#include <typeinfo>
#include <fstream>
using namespace std;
int main()
{
	MonsterCard dragon("Blue-Eyes White Dragon", "This legendary dragon is a powerful engine of destruction", 43, 3000, 2500);
	MonsterCard magician("Dark Magician", "The ultimate wizard.", 23, 2500, 2100);
	MagicCard swords("Swords of Revealing Light", "Your opponent's monsters cannot declare an attack.", 123, CardType::SPELL);
	MagicCard cylinder("Magic Cylinder", "Inflict damage to your opponent equal to its ATK.", 9,CardType::TRAP);
	PendelumCard timegazer("Timegazer Magician", "Your opponent cannot activate Trap Magic Cards", 3, 1200, 600, 8, CardType::SPELL);
	PendelumCard geriNikol("geri nikol", "twerk", 3, 1200, 600, 8, CardType::BUFF);


	std::cout << "************************** Test 1: expected true *********************************" << std::endl;
	std::cout << dragon.getRarity()<< " > " << magician.getRarity() << std::endl;
	std::cout << std::boolalpha << (dragon > magician) << std::endl;
	std::cout << "************************** End of Test 1 *****************************************" << std::endl << std::endl << std::endl;


	std::cout << "***************** Test 2: expected card at index 0 to be replaced by geriNikol ********************" << std::endl;
	Deck hulk = Deck("hulk");
	hulk.addCard(&timegazer);
	hulk.addCard(&magician);
	hulk.addCard(&cylinder);
	hulk.setCard(0, &geriNikol);
	std::cout<<hulk.getCards()[0]->getName() << std::endl;
	std::cout << "************************** End of Test 2  *********************************" << std::endl << std::endl << std::endl;

	std::cout << "***************** Test 3: expected error message for invalid setCard operation after shuffle ********************" << std::endl;
	hulk.shuffle();
	hulk.setCard(0, &timegazer);
	hulk.shuffle();
	hulk.shuffle();
	hulk.shuffle();

	std::cout << "************************** End of Test 3  *********************************" << std::endl << std::endl << std::endl;

	std::cout << "********* Test 4: expected true and information of firstDuelist to be saved in cylinder_deck file ************" << std::endl;
	Duelist firstDuelist("Ivan Ivanov");
	firstDuelist.getDeck().setDeckName("Magician Deck");
	firstDuelist.getDeck().addCard(&dragon);
	firstDuelist.getDeck().addCard(&swords);
	firstDuelist.getDeck().addCard(&magician);
	firstDuelist.getDeck().addCard(&cylinder);
	firstDuelist.getDeck().addCard(&timegazer);
	firstDuelist.getDeck().addCard(&geriNikol);
	firstDuelist.getDeck().shuffle();
	std::cout<<std::boolalpha<<firstDuelist.saveDeck("cylinder_deck.txt")<<std::endl;
	std::cout << firstDuelist.getDeck();

	std::cout << "************************** End of Test 4  *********************************" << std::endl << std::endl << std::endl;


	std::cout << "********* Test 5: expected invalid duel message due difference between duelists deck's count************" << std::endl;
	Duelist secondDuelis("Ethan Winters");
	secondDuelis.getDeck().setDeckName("Magician Deck");
	secondDuelis.getDeck().addCard(&dragon);
	secondDuelis.getDeck().addCard(&swords);
	secondDuelis.getDeck().addCard(&magician);
	secondDuelis.getDeck().addCard(&cylinder);
	secondDuelis.getDeck().addCard(&timegazer);
	/*secondDuelis.getDeck().addCard(&geriNikol);*/
	secondDuelis.getDeck().shuffle();
	firstDuelist.duel(secondDuelis);

	std::cout << "************************** End of Test 5  *********************************" << std::endl << std::endl << std::endl;


	std::cout << "********* Test 6: expected valid result of duel between first and second duelist************" << std::endl;

	secondDuelis.getDeck().addCard(&geriNikol);
	secondDuelis.getDeck().shuffle();
	duel(firstDuelist, secondDuelis);
	std::cout << "************************** End of Test 6 *********************************" << std::endl << std::endl << std::endl;



	std::cout << "********* Test 7: expected true and load deck into secondDuelist************" << std::endl;
	std::cout << secondDuelis.loadDeck("swords_deck.txt") << std::endl;
	std::cout << secondDuelis.getDeck();
	std::cout << "************************** End of Test 7 *********************************" << std::endl << std::endl << std::endl;

}