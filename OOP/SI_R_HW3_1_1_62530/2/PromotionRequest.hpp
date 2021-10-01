#pragma once
#include "Request.hpp"
class PromotionRequest:public Request
{
private:
	double amount;
public:
	PromotionRequest(const std::string& sender, const double& amount);
	double getAmount()const;
	
};