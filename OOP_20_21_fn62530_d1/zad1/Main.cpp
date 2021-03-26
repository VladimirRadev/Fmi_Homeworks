#include "drink.hpp"
#include "VendingMachine.hpp"
using namespace std;
int main()
{
	Drink c = Drink("Cola", 1002, 3.4, 2.99);
	Drink d = Drink("Fanta", 590, 2.5, 1.99);
	Drink f = Drink(d);
	f = c;
	Drink yeger = c;
	yeger.set_name("yeger");
	VendingMachine vd;
	vd.add_drink(f);
	vd.add_drink(c);
	vd.add_drink(d);
	vd.add_drink(yeger);
	
	int kur = 0;
	VendingMachine vk=VendingMachine(vd);
	Drink whisky = Drink("Whiskey",2500,0.700,14.99);
	Drink zagorka = Drink("Zagorka", 2500, 0.700, 14.99);
	cout << endl;
	vk.add_drink(whisky);
	/*cout<<vk.buy_drink("Cola", 2.99)<<endl;
	cout <<vk.buy_drink("Cola", 3) << endl;
	cout << vk.buy_drink("yeger", 14) << endl;
	cout << endl;
	cout << boolalpha<<vk.add_drink(whisky) << endl;
	cout << endl;
	cout << vk.buy_drink("Whiskey", 3) << endl;
	cout << vk.buy_drink("Whiskey", 15) << endl;
	vk.printVendingMachineItems();
	cout << boolalpha << vk.add_drink(whisky) << endl;
	cout << vk.buy_drink("Fanta", 3) << endl;
	cout << vk.buy_drink("Fanta", 3) << endl;
	cout << vk.buy_drink("Zagorka", 3) << endl;
	vk.printVendingMachineItems();
	cout << boolalpha << vk.add_drink(zagorka) << endl;
	cout << vk.add_drink(f)<<endl;
	cout << vk.buy_drink("Fanta", 2) << endl;
	cout << endl;
	vk.printVendingMachineItems();
	cout<<vk.get_income() << endl;*/
	vk.printVendingMachineItems();
	vk.buy_drink("Fanta", 10);
	//vk.buy_drink("Whiskey", 20);
	//vk.buy_drink("yeger", 10);
	cout << endl;
	vk.printVendingMachineItems();
	cout << endl;
	vk.buy_drink("Cola", 10);
	vk.add_drink(zagorka);
	cout << endl;
	vk.printVendingMachineItems();
	cout << endl;
	vk.buy_drink("Zagorka", 20);
	cout << endl;
	vk.printVendingMachineItems();
	cout << endl;

}