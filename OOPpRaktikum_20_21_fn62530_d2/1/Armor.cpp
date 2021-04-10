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
#include "Armor.hpp"
#include <iostream>

Armor::Armor()
{
	this->type = TypeArmor::none;
	this->defense = -1;
}
Armor::Armor(const TypeArmor& type, const int& defense)
{
	this->setType(type);
	this->setDefense(defense);
    
}
Armor::Armor(const Armor& rhs):type(rhs.getType()),defense(rhs.getDefense())
{
	for (int i = 0; i < rhs.getEffects().size(); i++)
	{
		std::pair < std::string, double>toAdd;
		toAdd.first = rhs.getEffects()[i].first;
		toAdd.second = rhs.getEffects()[i].second;
		this->effects.push_back(toAdd);

	}
}
Armor Armor::newCloth(const int& defense)
{
	return Armor(TypeArmor::cloth, defense);
}
Armor Armor::newLeather(const int& defense)
{
	return Armor(TypeArmor::leather, defense);
}
Armor Armor::newMail(const int& defense)
{
	return Armor(TypeArmor::mail, defense);
}
const std::string Armor::getStringType()const
{
	if (this->type == TypeArmor::none)
	{
		return "none";
	}
	if (this->type == TypeArmor::cloth)
	{
		return "cloth";
	}
	if (this->type == TypeArmor::leather)
	{
		return "leather";
	}
	if (this->type == TypeArmor::mail)
	{
		return "mail";
	}
}
const TypeArmor Armor::getType()const
{
	return this->type;
}
const int Armor::getDefense()const
{
	return this->defense;
}
const std::vector < std::pair<std::string, double>>& Armor::getEffects()const
{
	return this->effects;
}
void Armor::setType(const TypeArmor& type)
{
	if (type == TypeArmor::none)
	{
		std::cout << "TypeArmor of armor must be not none value" << std::endl;
		return;
	}
	this->type = type;
}
void Armor::setDefense(const int& defense)
{
	if (defense < 0)
	{
		std::cout << "Defense of armor must be non negative value" << std::endl;
		return;
	}
	else
	{
		this->defense = defense;
	}

}
void Armor::addNewEffect(const std::pair<std::string, double>& newEffect)
{
	for (int i = 0; i < this->effects.size(); i++)
	{
		//add only distinct effects's name, when we trying to add already existing
		//we replace already existing effect's efficiency with the new one's efficiency
		if (this->effects[i].first == newEffect.first)
		{
			this->effects[i].second = newEffect.second;
			return;
		}
	}
	this->effects.push_back(newEffect);
}
void Armor::removeEffect(const std::pair<std::string, double>& toRemoveEffect)
{
	if (!this->effects.empty())
	{
		for (int i = 0; i < this->effects.size(); i++)
		{
			//if name of effect is equal as toRemoveEffect's name
			//so delete it otherwise try with next element
			//We admit that effects will contain only unique effect's name
			if (this->effects[i].first == toRemoveEffect.first)
			{
				this->effects.erase(this->effects.begin() + i);
				return;
			}
		}
	}
	std::cout << "Set of effects doesn't contain given effect or it's empty. Try with existing!" << std::endl;
	return;
}
void Armor::updateEfficiencyOfEffect(const double& newEfficiency, const std::pair<std::string, double>& effectToUpdate)
{
	if (newEfficiency < 0.0)
	{
		std::cout << "New efficiency must be non-negative number" << std::endl;
		return;
	}
	if (!this->effects.empty())
	{
		for (int i = 0; i < this->effects.size(); i++)
		{
			//if name of effect is equal as toRemoveEffect's name
			//so delete it otherwise try with next element
			//We admit that effects will contain only unique effect's name
			if (this->effects[i].first == effectToUpdate.first)
			{
				this->effects[i].second = newEfficiency;
				return;
			}
		}
	}
	std::cout << "Set of effects doesn't contain given effect or it's empty. Try with existing!" << std::endl;
	return;

}
bool Armor::operator==(const Armor& rhs)const
{
	return (this->type == rhs.type && this->defense == rhs.defense);
}
int Armor::calcTakingSlots()const
{
	return 1;
}
double Armor::calcGearScore()const
{
	if (!this->effects.empty())
	{
		double result = 0.0;
		for (int i = 0; i < this->effects.size(); i++)
		{
			result += this->effects[i].second;
		}
		return result;
	}
	else
	{
		return 0.0;
	}
}