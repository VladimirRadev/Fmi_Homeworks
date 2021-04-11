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
#include <assert.h>
#include "Armor.hpp"
#include "Weapon.hpp"
#include"Equipment.hpp"
#include "Materials.hpp"
#include "Money.hpp"
#include "Backpack.hpp"
#include "Inventory.hpp"
#include <utility>
#include <vector>

void Test1()
{
	std::pair<double, double>hitDamage(3, 1.5);
	std::pair<double, double>hitDamage1(3, 1);
	std::pair<std::string, double>effect("poison  an enemy", 3);
	std::pair<std::string, double>effect1("stun enemy", 5);
	std::pair<std::string, double>effect2("faster running", 1);
	std::pair<std::string, double>effect3("heal hero", 2);
	Weapon weapon = Weapon::newAxe(hitDamage,TypeWeapon::one_handed);
	Weapon weapon1 = Weapon::newSpear(hitDamage1);
	weapon.addNewEffect(effect);
	weapon.addNewEffect(effect1);
	weapon.addNewEffect(effect2);
	weapon.changeTypeOfWeapon(TypeWeapon::one_handed);
	weapon.changeTypeOfWeapon(TypeWeapon::two_handed);
	weapon.changeClassificationOfWeapon(Classification::staff);
	weapon.removeEffect(effect);
	weapon.removeEffect(effect1);
	weapon.removeEffect(effect2);
	weapon.addNewEffect(effect);
	weapon.updateEfficiencyOfEffect(2, effect);
	weapon.changeClassificationOfWeapon(Classification::dagger);

	weapon1.addNewEffect(effect);
	weapon1.updateEfficiencyOfEffect(2, effect);
	weapon1.changeClassificationOfWeapon(Classification::mace,TypeWeapon::two_handed);
	Equipment<Weapon>eq;
	Equipment<Weapon>eq1;
	eq.addItem(weapon);
	eq1.addItem(weapon1);
	assert(weapon.getType() == TypeWeapon::one_handed);
	assert(weapon1.getStringClassification() == "mace");
	assert(weapon1.getType() == TypeWeapon::two_handed);
	assert(weapon.calcWeaponScore() == 3.1875);
	assert(weapon1.calcWeaponScore() == 6);
	assert(weapon.calcTakingSlots() == 1);
	assert(weapon1.calcTakingSlots() == 2);
	assert((eq == eq1) == false);
	return;
}
void Test2()
{
	std::pair<double, double>hitDamage(3, 1.5);
	std::pair<double, double>hitDamage1(3, 1);
	std::pair<std::string, double>effect("ubiva", 3);
	std::pair<std::string, double>effect1("razmazva", 5);
	std::pair<std::string, double>effect2("zadushavashto trushvane", 1);
	std::pair<std::string, double>effect3("go to sleep", 2);
	Armor armor1 = Armor::newCloth(20);
	Armor armor2 = Armor::newLeather(14);
	armor1.addNewEffect(effect);
	armor1.addNewEffect(effect1);
	armor2.addNewEffect(effect2);
	armor2.addNewEffect(effect3);
	armor1.removeEffect(effect1);
	armor2.removeEffect(effect3);
	armor1.setType(TypeArmor::mail);
	armor1.updateEfficiencyOfEffect(2, effect);

	assert(armor1.calcGearScore() == 2);
	assert(armor2.calcGearScore() == 1);
	assert(armor1.getType() == TypeArmor::mail);
	assert(armor2.getType() == TypeArmor::leather);
	assert(armor1.calcTakingSlots() == 1);
	assert(armor1.calcTakingSlots() == 1);

	Equipment<Armor>eq;
	assert(eq.isEquipmentEmpty() == true);
	eq.addItem(armor1);
	eq.addItem(armor2);
	assert(eq.bestEquipment() == armor1);
	assert(eq.isEquipmentFull() == false);
	eq.clearEquipment();
	assert(eq.isEquipmentEmpty() == true);
	eq.addItem(armor1);

	Equipment<Armor>eq1;
	eq1.addItem(armor2);
	
	//gearScore of eq is 2 but gearScore of eq1 is 1 (look at line 77 && 78)
	assert((eq == eq1)==false);
	assert((eq != eq1) == true);
	return;
}
void Test3()
{
	Materials materials;
	materials.addMaterial(20, TypeMaterials::essence);
	materials.removeMaterial(9, TypeMaterials::essence);
	materials.addMaterial(21, TypeMaterials::herbs);
	materials.addMaterial(41, TypeMaterials::ores);

	std::cout << "Test 3: Waiting for unsecsesfull message at next line!" << std::endl;
	std::cout << "********************************************************" << std::endl;
	//waiting for unsuccsesful message
	materials.removeMaterial(442, TypeMaterials::ores);
	std::cout << "********************************************************" << std::endl;
	std::cout << " \n \n";
	materials.addMaterial(21, TypeMaterials::cloth);

	assert(materials.calcTakingSlots() == 9);
	materials.clearMaterials();
	materials.addMaterial(21, TypeMaterials::essence);
	materials.removeMaterial(20, TypeMaterials::essence);
	assert(materials.calcTakingSlots() == 1);


	Money money;
	money.addMoney(2, 220);
	money.removeMoney(1, 90);
	money.removeMoney(2, 30);
	assert((money.getGold() == 0) && (money.getSilver() == 0));
	money.addMoney(0, 99);
	money.addMoney(0, 3);
	assert((money.getGold() == 1) && (money.getSilver() == 2));

}
void Test4()
{
	Equipment<Armor>armor;
	Armor armor1 = Armor::newCloth(20);
	Armor armor2 = Armor::newLeather(14);
	std::pair<std::string, double>effect("ubiva", 3);
	std::pair<std::string, double>effect1("razmazva", 5);
	std::pair<std::string, double>effect2("ubiva", 5);
	armor1.addNewEffect(effect);
	assert(armor1.getEffects()[0].second == 3);
	armor1.addNewEffect(effect1);
	armor1.addNewEffect(effect2);
	assert(armor1.getEffects()[0].second == 5);

	armor2.addNewEffect(effect);
	armor2.updateEfficiencyOfEffect(5, effect);

	armor.addItem(armor1);
	armor.addItem(armor2);
	assert(armor.bestEquipment() == armor1);
	assert(armor.getItems().size() == 2);
	armor.removeItem(armor1);
	assert(armor.getItems().size() == 1);
}
void Test5()
{
	Backpack<Money>wallet;
	wallet.addItem(2, 40);
	wallet.removeItem(2, 30);
	assert((wallet.getItem().getGold()==0)&&(wallet.getItem().getSilver()==10));
	wallet.clearBackpack();
	assert(wallet.isBackpackEmpty() == true);
	wallet.addItem(3, 11);
	wallet.addItem(0, 99);
	assert((wallet.getItem().getGold() == 4) && (wallet.getItem().getSilver() == 10));
	//Backpack<money> doesn't take any slots
	assert(wallet.getSlots() == 0);

	Backpack<Materials>materials;
	assert(materials.isBackpackEmpty() == true);
	materials.addItem(61, TypeMaterials::essence);
	materials.addItem(50, TypeMaterials::ores);
	assert(materials.getSlots() == 10);
	materials.addItem(120, TypeMaterials::cloth);
	assert(materials.getSlots() == 16);
	assert(materials.isBackpackFull() == true);
	materials.removeItem(20, TypeMaterials::cloth);
	materials.removeItem(12, TypeMaterials::ores);
	assert(materials.getSlots() == 14);
	assert(materials.isBackpackFull() == false);

}
void Test6()
{
	std::cout << "Test 6: \n";
	Backpack<Materials>materials;
	materials.addItem(61, TypeMaterials::essence);
	materials.addItem(50, TypeMaterials::ores);
	materials.addItem(120, TypeMaterials::cloth);
	materials.removeItem(20, TypeMaterials::cloth);
	materials.removeItem(12, TypeMaterials::ores);
	Inventory<Backpack<Materials>> materialsStorage(materials);
	Inventory<Backpack<Materials>> materialsStorage1(materials);
	std::cout << "***************************** \n";
	std::cout << materialsStorage1;
	assert((materialsStorage == materialsStorage1) == true);
	assert((materialsStorage != materialsStorage1)==false);
}
void Test7()
{
	std::cout << "Test 7: \n\n";
	Equipment<Armor>armorEquipment;
	Equipment<Armor>armorEquipment1;
	Armor armor1 = Armor::newCloth(20);
	Armor armor2 = Armor::newLeather(14);
	std::pair<std::string, double>effect("ubiva", 3);
	std::pair<std::string, double>effect1("razmazva", 5);
	std::pair<std::string, double>effect2("ubiva", 5);
	armor1.addNewEffect(effect);
	armor1.addNewEffect(effect1);
	//now effect "ubiva" must be set to from 3 to 5
	armor1.addNewEffect(effect2);
	armor2.addNewEffect(effect1);
	armorEquipment.addItem(armor1); // 10 gearScore
	armorEquipment1.addItem(armor2); //5 gearScore
	Inventory < Equipment<Armor>>armorStorage(armorEquipment);
	Inventory < Equipment<Armor>>armorStorage1(armorEquipment1);
	std::cout << "What contains armorStorage?: \n";
	std::cout << "***************************** \n";
	std::cout << armorStorage;
	std::cout << "What contains armorStorage1?: \n";
	std::cout << "***************************** \n";
	std::cout << armorStorage1;
	//now they take 1 slot because armorEquipment and armorEquipment1 contain a single armor within
	assert((armorStorage == armorStorage1) == true);
	armorEquipment.addItem(armor2);//10+5;
	armorStorage.updateItem(armorEquipment);
	std::cout << "What contains armorStorage?: \n";
	std::cout << "***************************** \n";
	std::cout << armorStorage;
	//now armorStorage1 contains a single armor within but instead it, armorStorage now contains 2 armors within
	assert((armorStorage == armorStorage1) == false);
	assert((armorStorage != armorStorage1) == true);
}
int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	std::cout << "succses! \n";

}