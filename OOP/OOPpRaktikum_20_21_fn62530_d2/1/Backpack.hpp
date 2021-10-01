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
#include <fstream>
#include "Money.hpp"
#include "Materials.hpp"

const int MAX_MATERIALS_SLOTS = 16;

template<class T>
class Backpack
{
private:
	T item;
	unsigned int slots;
public:
	Backpack<T>();
	Backpack<T>(const Backpack<T>& rhs);
	Backpack<T>& operator=(const Backpack<T>& rhs);
	bool isBackpackEmpty()const;
	bool isBackpackFull()const;
	const unsigned int& getSlots()const;
	const T& getItem()const;
	void clearBackpack();
	void addItem(const unsigned int& quantity, const TypeMaterials& material);
	void addItem(const unsigned int& gold, const unsigned int& silver);
	void removeItem(const unsigned int& quantity, const TypeMaterials& material);
	void removeItem(const unsigned int& gold, const unsigned int& silver);

};
template<class T>
Backpack<T>::Backpack<T>() : slots(0), item(T()) {}

template<class T>
Backpack<T>::Backpack<T>(const Backpack<T>& rhs) : slots(rhs.getSlots()), item(rhs.getItem()) {}
template<class T>
const T& Backpack<T>::getItem()const
{
	return this->item;
}

template<>
Backpack<Money>& Backpack<Money>::operator=(const Backpack<Money>& rhs)
{
	if (this != &rhs)
	{
		this->item.clearMoney();
		this->item.addMoney(rhs.getItem().getGold(), rhs.getItem().getSilver());
		this->slots = rhs.getSlots();
	}
	return *this;
}
template<>
Backpack<Materials>& Backpack<Materials>::operator=(const Backpack<Materials>& rhs)
{
	if (this != &rhs)
	{
		this->item.clearMaterials();
		for (int i = 0; i < rhs.getItem().getMaterials().size(); i++)
		{
			this->item.addMaterial(rhs.getItem().getMaterials()[i].second, rhs.getItem().getMaterials()[i].first);
		}
		this->slots = rhs.getSlots();
	}
	return *this;
}
template<class T>
bool Backpack<T>::isBackpackEmpty()const
{
	return (this->slots == 0);
}
template<class T>
bool Backpack<T>::isBackpackFull()const
{
	return (this->slots >= MAX_MATERIALS_SLOTS);
}
template<class T>
const unsigned int& Backpack<T>::getSlots()const
{
	return this->slots;
}
template<>
void Backpack<Materials>::clearBackpack()
{
	this->item.clearMaterials();
}
template<>
void Backpack<Money>::clearBackpack()
{
	this->item.clearMoney();
}
template<>
void Backpack<Materials>::addItem(const unsigned int& quantity, const TypeMaterials& material)
{
	this->item.addMaterial(quantity, material);
	this->slots = this->item.calcTakingSlots();
}
template<>
void Backpack<Money>::addItem(const unsigned int& gold, const unsigned int& silver)
{
	this->item.addMoney(gold, silver);
}
template<>
void Backpack<Materials>::removeItem(const unsigned int& quantity, const TypeMaterials& material)
{
	int currentTakingSlots = this->slots;
	this->item.removeMaterial(quantity, material);

	//no changes
	if (this->item.calcTakingSlots() == currentTakingSlots)
	{
		return;
	}
	else
	{
		this->slots = this->item.calcTakingSlots();
		return;
	}
}
template<>
void Backpack<Money>::removeItem(const unsigned int& gold, const unsigned int& silver)
{
	this->item.removeMoney(gold, silver);
	return;
}
