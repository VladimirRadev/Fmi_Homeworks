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
#include <utility>
#include <string>
#include "Backpack.hpp"
#include "Equipment.hpp"
#include <fstream>

template <class T>
class Inventory
{
private:
	T item;
public:
	Inventory<T>();
	Inventory<T>(const T&item);
	void updateItem(const T& item);
    friend std::ostream& operator<<(std::ostream& out, const Inventory<Equipment<Armor>>& inventory);
	friend std::ostream& operator<<(std::ostream& out, const Inventory<Equipment<Weapon>>& inventory);
	friend std::ostream& operator<<(std::ostream& out, const Inventory<Backpack<Money>>& inventory);
	friend std::ostream& operator<<(std::ostream& out, const Inventory<Backpack<Materials>>& inventory);
	bool operator==(const Inventory<T>& rhs);
	bool operator!=(const Inventory<T>& rhs);
};

template<class T>
Inventory<T>::Inventory<T>() : item(T()) {}

template<class T>
Inventory<T>::Inventory<T>(const T& item): item(item){}

template<class T>
void Inventory<T>::updateItem(const T& item)
{
	this->item = item;

}
//type, defense ,effects
std::ostream& operator<<(std::ostream& out, const Inventory<Equipment<Armor>>& inventory)
{
	out << "Armors available in Equipment are: \n\n";
	for (int i = 0; i < inventory.item.getItems().size(); i++)
	{
		out << "Armor " << i << ": " << "with type: " << inventory.item.getItems()[i].getStringType() << " ," << "with defense: "
			<< inventory.item.getItems()[i].getDefense() << "\n";
		out << "And effects: \n";
		for (int j = 0; j < inventory.item.getItems()[i].getEffects().size(); j++)
		{
			out << "Effect " << j << ": " << inventory.item.getItems()[i].getEffects()[j].first << " " <<
				inventory.item.getItems()[i].getEffects()[j].second << " \n";
		}
		out << "************************* \n\n\n";
	}
	return out;
}

//type, classification, hitDamage, effects
std::ostream& operator<<(std::ostream& out, const Inventory<Equipment<Weapon>>& inventory)
{
	out << "Weapons available In Equipment are: \n\n";
	for (int i = 0; i < inventory.item.getItems().size(); i++)
	{
		out << "Weapon " << i << ": " << "with type: " << inventory.item.getItems()[i].getStringType() 
			<<" ," << "with classification: "
			<< inventory.item.getItems()[i].getStringClassification() << "\n";

		out << "Has lowest hit damage: " << inventory.item.getItems()[i].getHitDamage().first
			<< " and highest hid damage: " << inventory.item.getItems()[i].getHitDamage().second << " \n";
		out << "And effects: \n";
		for (int j = 0; j < inventory.item.getItems()[i].getEffects().size(); j++)
		{
			out << "Effect " << j << ": " << inventory.item.getItems()[i].getEffects()[j].first << " " <<
				inventory.item.getItems()[i].getEffects()[j].second << " \n";
		}
		out << "************************* \n\n\n";
	}
	return out;
}

//gold, silver
std::ostream& operator<<(std::ostream& out, const Inventory<Backpack<Money>>& inventory)
{
	out << "Money available in Backpack: \n\n";
	out << "Gold: " << inventory.item.getItem().getGold() << ", and Silver: " << inventory.item.getItem().getSilver() << " \n";
	out << "*************************** \n\n\n";
	return out;
}
//TypeMaterial->quantity
std::ostream& operator<<(std::ostream& out, const Inventory<Backpack<Materials>>& inventory)
{
	out << "Materials with its quantity stored in Backpack: \n\n";
	for (int i = 0; i < inventory.item.getItem().getMaterials().size(); i++)
	{
		//Herbs -> quantity
		out << inventory.item.getItem().getStringType(inventory.item.getItem().getMaterials()[i].first) << " with quantity -> "
			<< inventory.item.getItem().getMaterials()[i].second << '\n';

	
	}
	out << "***************************** \n\n\n";
	return out;

}

template<class T>
bool Inventory<T>::operator==(const Inventory<T>& rhs)
{
	return (this->item.getSlots() == rhs.item.getSlots());
}
template<class T>
bool Inventory<T>::operator!=(const Inventory<T>& rhs)
{
	return !(*this == rhs);
}