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
#include<iostream>
#include <string>
#include <utility>
#include <vector>

const double MULTIPLYER_OF_ONE_HANDED = 0.75;
const double MULTIPLYER_OF_TWO_HANDED = 1.50;

enum class TypeWeapon
{
	none,
	one_handed,
	two_handed

};
enum class Classification
{
	none,
	axe,
	sword,
	dagger,
	mace,
	staff,
	spear
};

class Weapon
{
private:

	TypeWeapon type;
	Classification classification;
	//first->lowestHitDamage, second->highestHitDamage
	std::pair<double, double>hitDamage;
	std::vector<std::pair<std::string, double>> effects;
	
public:
	Weapon();
	Weapon(const TypeWeapon& type,const Classification& classfication,const std::pair<double, double>& hitDamage);
	Weapon(const Weapon& rhs);
	static Weapon newAxe(const std::pair<double, double>& hitDamage,const TypeWeapon& typeWeapon);
	static Weapon newSword(const std::pair<double, double>& hitDamage, const TypeWeapon& typeWeapon);
	static Weapon newDagger(const std::pair<double, double>& hitDamage);
	static Weapon newMace(const std::pair<double, double>& hitDamage, const TypeWeapon& typeWeapon);
	static Weapon newStaff(const std::pair<double, double>& hitDamage);
	static Weapon newSpear(const std::pair<double, double>& hitDamage);
	const std::string getStringType()const;
	const std::string getStringClassification()const;
	const std::pair<double, double>& getHitDamage()const;
	const std::vector<std::pair<std::string, double>>& getEffects()const;
	const TypeWeapon getType()const;
	void setType(const TypeWeapon& type);
	void changeClassificationOfWeapon(const Classification& newClassification, const TypeWeapon& newType = TypeWeapon::none);
	void changeTypeOfWeapon(const TypeWeapon& newType);
	void addNewEffect(const std::pair<std::string, double>&newEffect);
	void removeEffect(const std::pair<std::string, double>& toRemoveEffect);
	void updateEfficiencyOfEffect(const double& newEfficiency, const std::pair<std::string, double>& effectToUpdate);
	bool operator==(const Weapon& rhs)const;
	int calcTakingSlots()const;
	double calcWeaponScore()const;

};


