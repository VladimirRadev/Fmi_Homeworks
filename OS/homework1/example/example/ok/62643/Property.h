#pragma once
#include <iostream>

using namespace std;

class Property {
public:
	Property() = default;
	virtual string getType() const = 0;
	virtual double getPriceInLeva() const = 0;
	virtual unsigned getArea() const = 0;
private:
	string address;
	unsigned areaInSquareKm;
	double priceInEuro;
};