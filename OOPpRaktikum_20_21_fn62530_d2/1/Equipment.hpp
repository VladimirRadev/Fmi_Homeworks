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
#include <iostream>
#include <vector>
#include "Weapon.hpp"
#include "Armor.hpp"
const int MAX_SLOTS_CAPACITY = 24;

template<class T>
class Equipment
{
private:
	std::vector<T> items;
	unsigned int slots;
public:
	Equipment<T>();
	Equipment<T>(const Equipment& rhs);
	const std::vector<T>& getItems()const;
	const unsigned int& getSlots()const;
	bool isEquipmentEmpty()const;
	bool isEquipmentFull()const;
	void clearEquipment();
	void addItem(const T& item);
	void removeItem(const T& item);
	const T& bestEquipment()const;
	bool operator==(const Equipment<T>& rhs)const;
	bool operator!=(const Equipment<T>& rhs)const;

};
template<class T>
Equipment<T>::Equipment<T>():slots(0)
{
	
}

template<class T>
Equipment<T>::Equipment<T>(const Equipment& rhs):slots(rhs.getSlots())
{
	for (int i = 0; i < rhs.getItems().size(); i++)
	{
		T item = rhs.getItems()[i];
		this->items.push_back(item);
	}
}

template<class T>
const std::vector<T>& Equipment<T>::getItems()const
{
	return this->items;
}

template<class T>
const unsigned int& Equipment<T>::getSlots()const
{
	return this->slots;
}
template<class T>
bool Equipment<T>::isEquipmentEmpty()const
{
	return this->slots == 0;

}
template<class T>
bool Equipment<T>::isEquipmentFull()const
{
	return this->slots >= MAX_SLOTS_CAPACITY;

}
template<class T>
void Equipment<T>::clearEquipment()
{
	this->items.clear();
	this->slots = 0;
}
template<class T>
void Equipment<T>::addItem(const T& item)
{
	if (this->slots + item.calcTakingSlots() > MAX_SLOTS_CAPACITY)
	{
		std::cout << "Equipment is full. No more available slots!" << std::endl;
		return;
	}
	this->items.push_back(item);
	this->slots += item.calcTakingSlots();
	return;
}
template<class T>
void Equipment<T>::removeItem(const T& item)
{
	if (this->isEquipmentEmpty())
	{
		std::cout << "No items inside equipment! Remove operataion isn't available" << std::endl;
		return;
	}
	for (int i = 0; i < this->items.size(); i++)
	{
		if (this->items[i] == item)
		{
			this->items.erase(this->items.begin() + i);
			this->slots -= item.calcTakingSlots();
			return;
		}
	}
	std::cout << "No such item exsist in items. Try with available " << std::endl;
	return;
}
template<class T>
const T& Equipment<T>::bestEquipment()const
{
	return T();
}
template<>
const Armor& Equipment<Armor>::bestEquipment()const
{
	if (this->isEquipmentEmpty())
	{
		return Armor();
	}
	int bestScoreIndex = -1;
	double maxScore = -1;
	for (int i = 0; i < this->items.size(); i++)
	{
		if (this->items[i].calcGearScore() > maxScore)
		{
			maxScore = this->items[i].calcGearScore();
			bestScoreIndex = i;
		}
	}
	return this->items[bestScoreIndex];
}
template<>
const Weapon& Equipment<Weapon>::bestEquipment()const
{
	if (this->isEquipmentEmpty())
	{
		return Weapon();
	}
	int bestScoreIndex = -1;
	double maxScore = -1;
	for (int i = 0; i < this->items.size(); i++)
	{
		if (this->items[i].calcWeaponScore() > maxScore)
		{
			maxScore = this->items[i].calcWeaponScore();
			bestScoreIndex = i;
		}
	}
	return this->items[bestScoreIndex];
}

template<>
bool Equipment<Armor>::operator==(const Equipment<Armor>& rhs)const
{
	if (this->isEquipmentEmpty() && rhs.isEquipmentEmpty())
	{
		return true;
	}
	double totalScoreOfThis = 0.0;
	for (int i = 0; i < this->items.size(); i++)
	{
		totalScoreOfThis += this->items[i].calcGearScore();
	}
	double totalScoreOfRhs = 0.0;
	for (int i = 0; i < rhs.items.size(); i++)
	{
		totalScoreOfRhs += rhs.items[i].calcGearScore();
	}
	return (totalScoreOfThis == totalScoreOfRhs);
}
template<>
bool Equipment<Weapon>::operator==(const Equipment<Weapon>& rhs)const
{
	if (this->isEquipmentEmpty() && rhs.isEquipmentEmpty())
	{
		return true;
	}
	double totalScoreOfThis = 0.0;
	for (int i = 0; i < this->items.size(); i++)
	{
		totalScoreOfThis += this->items[i].calcWeaponScore();
	}
	double totalScoreOfRhs = 0.0;
	for (int i = 0; i < rhs.items.size(); i++)
	{
		totalScoreOfRhs += rhs.items[i].calcWeaponScore();
	}
	return (totalScoreOfThis == totalScoreOfRhs);
}

template<class T>
bool Equipment<T>::operator!=(const Equipment<T>& rhs)const
{
	return !(*this == rhs);
}


