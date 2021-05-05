#pragma once
#include <string>
#include "LeavingRequest.hpp"
#include "PromotionRequest.hpp"
class TeamLead;
class Developer
{
protected:
	std::string name;
	double salary;
	TeamLead* leader;
public:
	Developer(const std::string& name);
	virtual ~Developer();
	std::string getName()const;
	double getSalary()const;
	void setSalary(const double& newSalary);
	TeamLead* getTeamLead();
	void setTeamLead(TeamLead* newLeader);
	void setInitialSalary(double amount);
	void sendLeavingRequest();
	void sendPromotionRequest(double amount);
};