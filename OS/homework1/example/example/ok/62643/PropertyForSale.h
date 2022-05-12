#pragma once
#include "Property.h"

class PropertyForSale:public Property {
public:
	PropertyForSale();
	PropertyForSale(string adr, unsigned area, double price, double deposit);
	virtual string getType() const override;
	virtual double getPriceInLeva() const override;
	double getDeposit() const;
	virtual unsigned getArea() const override;
private:
	string address;
	unsigned areaInSquareKm;
	double priceInEuro;
	double depositAmount;
};