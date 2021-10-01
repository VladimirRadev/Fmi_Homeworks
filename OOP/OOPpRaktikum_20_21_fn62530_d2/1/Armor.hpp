/**
* Solution to homework assignment 2
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
#include <vector>
#include <utility>
#include <string>
enum class TypeArmor
{
	none,
	cloth,
	leather,
	mail
};

class Armor
{
private:
	TypeArmor type;
	int defense;
	std::vector < std::pair<std::string, double>>effects;
public:
	Armor();
	Armor(const TypeArmor& type, const int& defense);
	Armor(const Armor& rhs);
	static Armor newCloth(const int& defense);
	static Armor newLeather(const int& defense);
	static Armor newMail(const int& defense);
	const std::string getStringType()const;
	const TypeArmor getType()const;
	const int getDefense()const;
	const std::vector < std::pair<std::string, double>>& getEffects()const;
	void setType(const TypeArmor& type);
	void setDefense(const int& defense);
	void addNewEffect(const std::pair<std::string, double>& newEffect);
	void removeEffect(const std::pair<std::string, double>& toRemoveEffect);
	void updateEfficiencyOfEffect(const double& newEfficiency, const std::pair<std::string, double>& effectToUpdate);
	bool operator==(const Armor& rhs)const;
	int calcTakingSlots()const;
	double calcGearScore()const;

};
