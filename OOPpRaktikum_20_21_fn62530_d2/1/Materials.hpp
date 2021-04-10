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
#include <utility>
#include <vector>
#include <cmath>
enum class TypeMaterials
{
	herbs,
	ores,
	cloth,
	essence
};

class Materials
{
private:
	std::vector < std::pair<TypeMaterials, unsigned int>>materials;
	//static std::vector < std::pair<TypeMaterials, unsigned int>>& generateMaterials();
public:
	Materials();
	Materials(const Materials& rhs);
	void addMaterial(const unsigned int& quantity,const TypeMaterials&material);
	void removeMaterial(const unsigned int& quantity, const TypeMaterials& material);
	const std::string getStringType(const TypeMaterials& material)const;
	const std::vector < std::pair<TypeMaterials, unsigned int>>& getMaterials()const;
	void clearMaterials();
	unsigned int calcTakingSlots()const;

};

