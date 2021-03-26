#include "drink.hpp"
int Drink::sizeOfStr(const char* str)const
{
	int size = 0;
	while (*(str + size) != '\0')
	{
		++size;
	}
	return size;
}
Drink::Drink():name(nullptr), quantity(0.0), calories(0),price(0.0)
{

}
Drink::Drink(const char* init_name, const int init_calories, const double& init_quantity, const double& init_price)
{
	this->set_name(init_name);
	this->calories = init_calories;
	this->quantity = init_quantity;
	this->price = init_price;
}
Drink::Drink(const Drink& copyDrink)
{
	this->set_name(copyDrink.get_name());
	this->calories = copyDrink.get_calories();
	this->quantity = copyDrink.get_quantity();
	this->price = copyDrink.get_price();
}
Drink& Drink::operator=(const Drink& rhs)
{
	if (this != &rhs)
	{
		this->set_name(rhs.get_name());
		this->calories = rhs.get_calories();
		this->quantity = rhs.get_quantity();
		this->price = rhs.get_price();

	}
	return *this;
}
Drink::~Drink()
{
	delete[]name;
}
const char* Drink::get_name() const
{
	return name;
}
int Drink::get_calories() const
{
	return calories;
}
double Drink::get_quantity() const
{
	return quantity;
}
double Drink::get_price() const
{
	return price;

}
void Drink::set_name(const char* new_name)
{
	delete[]name;
	int sizeOfNewName = sizeOfStr(new_name);
	name = new char[sizeOfNewName + 1];
	for (int i = 0; i < sizeOfNewName; i++)
	{
		name[i] = new_name[i];
	}
	name[sizeOfNewName] = '\0';
	return;
}
void Drink::printDrink()const
{
	cout << "Drink: " << this->get_name() << " , " << this->get_price() << " price, and quantity: " << this->get_quantity() << endl;
}