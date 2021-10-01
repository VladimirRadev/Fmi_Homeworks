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
#include "Materials.hpp"

//Im doing this functionality here, because i've tried to implement a static method
//which was doing the same functionality and has a return type vector<pair<TypeMaterials,unsigned int>> &
//but when i tried to assign the result of static method to this->materials
//(this->materials=Materials::generateMaterials()) operator= wasn't working, i mean Materials::generateMaterials()
//performed its functionality but copy of it wasn't assigned to this->materials, so i did it that
Materials::Materials()
{
	std::pair<TypeMaterials, unsigned int>herbs;
	herbs.first = TypeMaterials::herbs;
	herbs.second = 0;
	this->materials.push_back(herbs);

	std::pair<TypeMaterials, unsigned int>ores;
	ores.first = TypeMaterials::ores;
	ores.second = 0;
	this->materials.push_back(ores);

	std::pair<TypeMaterials, unsigned int>cloth;
	cloth.first = TypeMaterials::cloth;
	cloth.second = 0;
	this->materials.push_back(cloth);

	std::pair<TypeMaterials, unsigned int>essence;
	essence.first = TypeMaterials::essence;
	essence.second = 0;
	this->materials.push_back(essence);
}
Materials::Materials(const Materials& rhs)
{
	for (int i = 0; i < rhs.getMaterials().size(); i++)
	{
		std::pair<TypeMaterials, unsigned int>toAdd;
		toAdd.first = rhs.getMaterials()[i].first;
		toAdd.second = rhs.getMaterials()[i].second;
		this->materials.push_back(toAdd);
	}
}
void Materials::addMaterial(const unsigned int& quantity, const TypeMaterials& material)
{
	for (int i = 0; i < this->materials.size(); i++)
	{
		if (this->materials[i].first == material)
		{
			this->materials[i].second += quantity;
			return;
		}
	}
	return;
}
void Materials::removeMaterial(const unsigned int& quantity, const TypeMaterials& material)
{
	for (int i = 0; i < this->materials.size(); i++)
	{
		if (this->materials[i].first == material)
		{
			if ((int)(this->materials[i].second - quantity)< 0)
			{
				std::cout << "Can't substract that quantity. Too much for this material!" << std::endl;
				return;
			}
			this->materials[i].second -= quantity;
			return;
		}
	}
	return;
}
const std::string Materials::getStringType(const TypeMaterials& material)const
{
	if (material == TypeMaterials::cloth)
	{
		return "cloth";
	}
	if (material == TypeMaterials::essence)
	{
		return "essence";
	}
	if (material == TypeMaterials::herbs)
	{
		return "herbs";
	}
	if (material == TypeMaterials::ores)
	{
		return "ores";
	}

}
const std::vector < std::pair<TypeMaterials, unsigned int>>& Materials::getMaterials()const
{
	return this->materials;
}
void Materials::clearMaterials()
{
	for (int i = 0; i < this->materials.size(); i++)
	{
		this->materials[i].second = 0;
	}
	return;
}
unsigned int Materials::calcTakingSlots()const
{
	unsigned int takingSlots = 0;
	for (int i = 0; i < this->materials.size(); i++)
	{
		if (this->materials[i].first == TypeMaterials::essence)
		{
			takingSlots +=ceil(this->materials[i].second / 10.0);

		}
		//some of other 3 types: herbs ,cloth, ores
		else
		{
			takingSlots += ceil(this->materials[i].second / 20.0);
		}
	}
	return takingSlots;
}