#pragma once
#include "Property.h"

class PropertyForRent: public Property {
public:
	PropertyForRent();
	PropertyForRent(string address, unsigned areaInSquareKm, double priceInEuro, string landHolder);
	virtual string getType() const override;
	virtual double getPriceInLeva() const override;
	string getHolder() const;
	virtual unsigned getArea() const override;
private:
	string address;
	unsigned areaInSquareKm;
	double priceInEuro;
	string landlordName;
};