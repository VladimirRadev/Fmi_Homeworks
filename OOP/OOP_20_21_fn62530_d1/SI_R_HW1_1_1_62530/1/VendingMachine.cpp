#include "drink.hpp"
#include "VendingMachine.hpp"
int VendingMachine::sizeOfStr(const char* str)const
{
	int size = 0;
	while (*(str + size) != '\0')
	{
		++size;
	}
	return size;
}
bool VendingMachine::areEqual(const char* str1Name, const char* str2Name)const
{
	int sizeOfStr1Name = sizeOfStr(str1Name);
	int sizeOfStr2Name = sizeOfStr(str2Name);
	if (sizeOfStr1Name != sizeOfStr2Name)
	{
		return false;
	}
	else
	{
		bool flag = true;
		for (int i = 0; i < sizeOfStr1Name; i++)
		{
			if (str1Name[i] != str2Name[i])
			{
				flag = false;
				break;
			}
		}
		return flag;
	}
}
VendingMachine::VendingMachine() :count(0), capacity(2),incomeMoney(0.0)
{
	drinks = new Drink[capacity];
}
VendingMachine::VendingMachine(const VendingMachine& from)
{
	delete[]this->drinks;
	if (from.getCount() == 0)
	{
		this->count = 0;
		this->capacity = 1;
		this->drinks = new Drink[this->capacity];
		this->incomeMoney = from.incomeMoney;
	}
	else
	{
		this->drinks = new Drink[from.getCount()];
		for (int i = 0; i < from.getCount(); i++)
		{
			this->drinks[i] = from.getDrinks()[i];
		}
		this->count = from.getCount();
		//because we are alocate memory only for from.getCount() elements and 
		//if from's capacity is bigger than from's count then with add drink method 
		//will be write in foreign memory
		this->capacity = from.getCount();
		this->incomeMoney = from.incomeMoney;
	}

}
VendingMachine& VendingMachine::operator=(const VendingMachine& from)
{
	if (this != &from)
	{
		delete[]this->drinks;
		if (from.getCount() == 0)
		{
			this->count = 0;
			this->capacity = 1;
			this->drinks = new Drink[this->capacity];
			this->incomeMoney = from.incomeMoney;
		}
		else
		{


			this->drinks = new Drink[from.getCount()];
			for (int i = 0; i < from.getCount(); i++)
			{
				this->drinks[i] = from.getDrinks()[i];
			}
			this->count = from.getCount();

			//because we are alocate memory only for from.getCount() elements and 
			//if from's capacity is bigger than from's count then with add drink method 
			//will be write in foreign memory
			this->capacity = from.getCount();
			this->incomeMoney = from.incomeMoney;
		}
	}
	return *this;
}
VendingMachine::~VendingMachine()
{
	delete[]drinks;
}
const Drink* VendingMachine::getDrinks()const
{
	return drinks;
}
int VendingMachine::getCount()const
{
	return this->count;
}
int VendingMachine::getCapacity()const
{
	return this->capacity;
}
bool VendingMachine::add_drink(const Drink& to_add)
{
	for (int i = 0; i < this->getCount(); i++)
	{
		if (areEqual(this->drinks[i].get_name(), to_add.get_name()))
		{
			return false;
		}
	}
	if (count + 1 > capacity)
	{
		capacity *= 2;
		Drink* newDrinks = new Drink[capacity];
		for (int i = 0; i < this->getCount(); i++)
		{
			newDrinks[i] = this->drinks[i];
		}
		newDrinks[count] = to_add;
		++count;
		delete[]this->drinks;
		this->drinks = newDrinks;

		return true;

	}
	else
	{
		this->drinks[count] = to_add;
		++count;
		return true;
	}
}
int VendingMachine::buy_drink(const char* drink_name, const double money)
{
	for (int i = 0; i < this->getCount(); i++)
	{
		if (areEqual(this->drinks[i].get_name(), drink_name))
		{
			if (this->drinks[i].get_price() <= money)
			{
				if (this->count == 1)
				{
					Drink* newDrinks = new Drink[this->count];
					newDrinks[0] = this->drinks[0];
					delete[]this->drinks;
					this->drinks = newDrinks;
					count = 0;
					capacity = 1;
					this->incomeMoney += money;
					return 0;
				}
				Drink* newDrinks = new Drink[count - 1];
				for (int j = 0; j < i; j++)
				{
					newDrinks[j] = this->drinks[j];

				}
				for (int k = i; k < count - 1; k++)
				{
					newDrinks[k] = this->drinks[k + 1];
				}
				delete[]this->drinks;
				this->drinks = newDrinks;
				--count;
				capacity = count;
				this->incomeMoney += money;
				return 0;
			}
			else
			{
				this->incomeMoney += money;
				return 1;
			}
		}
	}
	return 2;
}
double VendingMachine::get_income() const
{
	return this->incomeMoney;
}
void VendingMachine::printVendingMachineItems()const
{
	for (int i = 0; i < this->getCount(); i++)
	{
		drinks[i].printDrink();
	}
}