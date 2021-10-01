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
#include "Weapon.hpp"

Weapon::Weapon()
{
	this->type = TypeWeapon::none;
	this->classification = Classification::none;
	this->hitDamage.first = 0.0;
	this->hitDamage.second = 0.0;

}
Weapon::Weapon(const TypeWeapon& type, const Classification& classfication, const std::pair<double, double>& hitDamage)
{
	this->type = type;
	this->classification = classfication;
	if (hitDamage.first < 0.0)
	{
		this->hitDamage.first = 0.0;
	}
	else
	{
		this->hitDamage.first = hitDamage.first;
	}
	if (hitDamage.second < 0.0)
	{
		this->hitDamage.second = 0.0;
	}
	else
	{
		this->hitDamage.second = hitDamage.second;
	}
}
Weapon::Weapon(const Weapon& rhs):type(rhs.getType()),classification(rhs.classification)
{
	this->hitDamage.first = rhs.getHitDamage().first;
	this->hitDamage.second = rhs.getHitDamage().second;
	for (int i = 0; i < rhs.getEffects().size(); i++)
	{
		std::pair < std::string, double>toAdd;
		toAdd.first = rhs.getEffects()[i].first;
		toAdd.second = rhs.getEffects()[i].second;
		this->effects.push_back(toAdd);
	}
}
Weapon Weapon::newAxe(const std::pair<double, double>& hitDamage, const TypeWeapon& typeWeapon)
{
	//can be one or two handed
	return Weapon(typeWeapon, Classification::axe, hitDamage);

}
Weapon Weapon::newSword(const std::pair<double, double>& hitDamage,const TypeWeapon& typeWeapon)
{
	//can be one or two handed
	return Weapon(typeWeapon, Classification::sword, hitDamage);
}
Weapon Weapon::newDagger(const std::pair<double, double>& hitDamage)
{
	//must be one_handed
	return Weapon(TypeWeapon::one_handed, Classification::dagger, hitDamage);
}
Weapon Weapon::newMace(const std::pair<double, double>& hitDamage,const TypeWeapon& typeWeapon)
{
	//can be one or two handed
	return Weapon(typeWeapon, Classification::mace, hitDamage);
}
Weapon Weapon::newStaff(const std::pair<double, double>& hitDamage)
{
	//myst be two_handed always
	return Weapon(TypeWeapon::two_handed, Classification::staff, hitDamage);
}
Weapon Weapon::newSpear(const std::pair<double, double>& hitDamage)
{
	//can be only one_handede
	return Weapon(TypeWeapon::one_handed, Classification::spear, hitDamage);
}
const std::string Weapon::getStringType()const
{
	if (this->getType() == TypeWeapon::none)
	{
		return "none";
	}
	if (this->getType() == TypeWeapon::one_handed)
	{
		return "one_handed";
	}
	if (this->getType() == TypeWeapon::two_handed)
	{
		return "two_handed";
	}

}
const std::string Weapon::getStringClassification()const
{
	if (this->classification == Classification::none)
	{
		return "none";
	}
	if (this->classification == Classification::axe)
	{
		return "axe";
	}
	if (this->classification == Classification::dagger)
	{
		return "dagger";
	}
	if (this->classification == Classification::sword)
	{
		return "sword";
	}
	if (this->classification == Classification::mace)
	{
		return "mace";
	}
	if (this->classification == Classification::staff)
	{
		return "staff";
	}
	if (this->classification == Classification::spear)
	{
		return "spear";
	}
}
const std::pair<double, double>& Weapon::getHitDamage()const
{
	return this->hitDamage;
}
const std::vector<std::pair<std::string, double>>& Weapon::getEffects()const
{
	return this->effects;
}
const TypeWeapon Weapon::getType()const
{
	return this->type;
}
void Weapon::setType(const TypeWeapon& type)
{
	this->type = type;
}
void Weapon::changeClassificationOfWeapon(const Classification& newClassification,
	const TypeWeapon& newType)
{
	if (newClassification == Classification::none)
	{
		return;
	}
	else if (newClassification == Classification::axe)
	{
		if (newType == TypeWeapon::one_handed)
		{
			this->classification = Classification::axe;
			this->setType(TypeWeapon::one_handed);
			return;
		}
		else if (newType == TypeWeapon::two_handed)
		{
			this->classification = Classification::axe;
			this->setType(TypeWeapon::two_handed);
			return;
		}
		else
		{
			std::cout << "Must give as second argument new specific type for axe (one or two_handed)!" << std::endl;
			return;
		}
		
	}
	else if (newClassification == Classification::sword)
	{
		if (newType == TypeWeapon::one_handed)
		{
			this->classification = Classification::sword;
			this->setType(TypeWeapon::one_handed);
			return;
		}
		else if (newType == TypeWeapon::two_handed)
		{
			this->classification = Classification::sword;
			this->setType(TypeWeapon::two_handed);
			return;
		}
		else
		{
			std::cout << "Must give as second argument new specific type for sword (one or two_handed)!" << std::endl;
			return;
		}
	}
	else if (newClassification == Classification::dagger)
	{
		if (newType != TypeWeapon::none)
		{
			std::cout << "Dagger' s type must always been one_handed. Can't change to other" << std::endl;
			return;
		}
		this->classification = Classification::dagger;
		this->setType(TypeWeapon::one_handed);
	}
	else if (newClassification == Classification::mace)
	{
		if (newType == TypeWeapon::one_handed)
		{
			this->classification = Classification::mace;
			this->setType(TypeWeapon::one_handed);
			return;
		}
		else if (newType == TypeWeapon::two_handed)
		{
			this->classification = Classification::mace;
			this->setType(TypeWeapon::two_handed);
			return;
		}
		else
		{
			std::cout << "Must give as second argument new specific type for mace (one or two_handed)!" << std::endl;
			return;
		}
	}
	else if (newClassification == Classification::staff)
	{
		if (newType != TypeWeapon::none)
		{
			std::cout << "Staff' s type must always been two_handed. Can't change to other" << std::endl;
			return;
		}
		this->classification = Classification::staff;
		this->setType(TypeWeapon::two_handed);
	}
	else if (newClassification == Classification::spear)
	{
		if (newType != TypeWeapon::none)
		{
			std::cout << "Spear' s type must always been one_handed. Can't change to other" << std::endl;
			return;
		}
		this->classification = Classification::spear;
		this->setType(TypeWeapon::one_handed);
	}
	else
	{
		return;
	}
}
void Weapon::changeTypeOfWeapon(const TypeWeapon& newType)
{
	if (this->classification == Classification::none)
	{
		std::cout << "Must set classification of weapon firstable and then can change type of weapon!" << std::endl;
		return;
	}
	else if (this->classification== Classification::axe)
	{
		if (newType == TypeWeapon::one_handed)
		{
			this->setType(TypeWeapon::one_handed);
			return;
		}
		else if (newType == TypeWeapon::two_handed)
		{
			this->setType(TypeWeapon::two_handed);
			return;
		}
		else
		{
			std::cout << "Axe's type can't be: " <<"none !"<<std::endl;
			return;
		}

	}
	else if (this->classification == Classification::sword)
	{
		if (newType == TypeWeapon::one_handed)
		{
			this->setType(TypeWeapon::one_handed);
			return;
		}
		else if (newType == TypeWeapon::two_handed)
		{
			this->setType(TypeWeapon::two_handed);
			return;
		}
		else
		{
			std::cout << "Sword's type can't be: " << "none !" << std::endl;
			return;
		}
	}
	else if (this->classification == Classification::dagger)
	{
		if (newType != TypeWeapon::one_handed)
		{
			std::cout << "Dagger' s type must always been one_handed. Can't change to other" << std::endl;
			return;
		}
		this->setType(TypeWeapon::one_handed);
	}
	else if (this->classification == Classification::mace)
	{
		if (newType == TypeWeapon::one_handed)
		{
			this->setType(TypeWeapon::one_handed);
			return;
		}
		else if (newType == TypeWeapon::two_handed)
		{
			this->setType(TypeWeapon::two_handed);
			return;
		}
		else
		{
			std::cout << "Mace's type can't be: " << "none !" << std::endl;
			return;
		}
	}
	else if (this->classification == Classification::staff)
	{
		if (newType != TypeWeapon::two_handed)
		{
			std::cout << "Staff' s type must always been two_handed. Can't change to other" << std::endl;
			return;
		}
		this->setType(TypeWeapon::two_handed);
	}
	else if (this->classification == Classification::spear)
	{
		if (newType != TypeWeapon::one_handed)
		{
			std::cout << "Spear' s type must always been one_handed. Can't change to other" << std::endl;
			return;
		}
		this->setType(TypeWeapon::one_handed);
	}
	else
	{
		return;
	}
}
void Weapon::addNewEffect(const std::pair<std::string, double>& newEffect)
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
void Weapon::removeEffect(const std::pair<std::string, double>& toRemoveEffect)
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
void Weapon::updateEfficiencyOfEffect(const double& newEfficiency, const std::pair<std::string, double>& effectToUpdate)
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
bool Weapon::operator==(const Weapon& rhs)const
{
	return(this->type == rhs.type && this->classification == rhs.classification);
}
int Weapon::calcTakingSlots()const
{
	if (this->getType() == TypeWeapon::one_handed)
	{
		return 1;
	}
	else if (this->getType() == TypeWeapon::two_handed)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}
double Weapon::calcWeaponScore()const
{
	double result = 0.0;
	double avarageHitDamage = (double)(this->hitDamage.first + this->hitDamage.second) / 2.0;
	double sumOfEfficiencyOfEffects = 0.0;
	if (!this->effects.empty())
	{
		for (int i = 0; i < this->effects.size(); i++)
		{
			sumOfEfficiencyOfEffects += this->effects[i].second;
		}
		if (this->type == TypeWeapon::one_handed)
		{
			result = (avarageHitDamage + sumOfEfficiencyOfEffects) * MULTIPLYER_OF_ONE_HANDED;
			return result;
		}
		else if (this->type == TypeWeapon::two_handed)
		{
			result = (avarageHitDamage + sumOfEfficiencyOfEffects) * MULTIPLYER_OF_TWO_HANDED;
			return result;
		}
		else
		{

			return 0.0;
		}

	}
	else
	{
		if (this->type == TypeWeapon::one_handed)
		{
			result = avarageHitDamage * MULTIPLYER_OF_ONE_HANDED;
			return result;
		}
		else if (this->type == TypeWeapon::two_handed)
		{
			result = avarageHitDamage * MULTIPLYER_OF_TWO_HANDED;
			return result;
		}
		else
		{
			return 0.0;
		}
	}



}