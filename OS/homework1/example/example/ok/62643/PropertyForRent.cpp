#include "PropertyForRent.h"

PropertyForRent::PropertyForRent() {
	this->address = string();
	this->areaInSquareKm = 0;
	this->landlordName = string();
	this->priceInEuro = 0;
}
PropertyForRent::PropertyForRent(string address, unsigned areaInSquareKm, double priceInEuro, string landHolder) {
	this->address = address;
	this->areaInSquareKm = areaInSquareKm;
	this->landlordName = landHolder;
	this->priceInEuro = priceInEuro;
}
string PropertyForRent::getType() const  {
	return "For Rent";
}
double PropertyForRent::getPriceInLeva() const {
	return this->priceInEuro * 1.95583;
}

unsigned PropertyForRent::getArea() const {
	return this->areaInSquareKm;
}

string PropertyForRent::getHolder() const {
	return this->landlordName;
}