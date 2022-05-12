#include "PropertyForSale.h"


PropertyForSale::PropertyForSale() {
	this->address = string();
	this->areaInSquareKm = 0;
	this->priceInEuro = 0;
	this->depositAmount = 0;
}

PropertyForSale::PropertyForSale(string adr, unsigned area, double price, double deposit) {
	this->address = adr;
	this->areaInSquareKm = area;
	this->priceInEuro = price;
	this->depositAmount = deposit;
}
string PropertyForSale::getType() const {
	return "For Sale";
}

double PropertyForSale::getPriceInLeva() const {
	return this->priceInEuro * 1.95583;
}

unsigned PropertyForSale::getArea() const {
	return this->areaInSquareKm;
}

double PropertyForSale::getDeposit() const {
	return this->depositAmount;
}