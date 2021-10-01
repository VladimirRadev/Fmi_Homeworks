#ifndef VendingMachine1
#define VendingMachine1 1

#include"drink.hpp"

class VendingMachine {
public:
    VendingMachine();
    VendingMachine(const VendingMachine& from);
    VendingMachine& operator=(const VendingMachine& from);

    bool add_drink(const Drink& to_add);
    int buy_drink(const char* drink_name, const double money);

    double get_income() const;

    ~VendingMachine();
    const Drink* getDrinks()const;
    int getCount()const;
    int getCapacity()const;
    void printVendingMachineItems()const;
private:
    Drink* drinks;
    int count;
    int capacity;
    double incomeMoney;
    int sizeOfStr(const char* str)const;
    bool areEqual(const char* str1Name, const char* str2Name)const;
};
#endif