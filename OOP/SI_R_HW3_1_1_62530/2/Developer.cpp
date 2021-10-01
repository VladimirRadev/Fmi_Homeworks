#include "Developer.hpp"
#include "TeamLead.hpp"
Developer::Developer(const std::string& name):name(name),salary(0.0),leader(nullptr){}
Developer::~Developer()
{
	this -> leader = nullptr;
	delete leader;
}
std::string Developer::getName()const
{
	return name;
}
double Developer::getSalary()const
{
	return salary;
}
void Developer::setSalary(const double& newSalary)
{
	this->salary = newSalary;
}
TeamLead* Developer::getTeamLead()
{
	return leader;
}
void Developer::setTeamLead(TeamLead* newLeader)
{
	this->leader = newLeader;
}
void Developer::setInitialSalary(double amount)
{
	if (this->salary == 0.0)
	{
		this->salary = amount;
	}
	return;
}

void Developer::sendLeavingRequest()
{
	if (this->getTeamLead() == nullptr)
	{
		return;
	}
	LeavingRequest leaveRequest(this->getName());
    this->getTeamLead()->addLeavingRequest(leaveRequest);
}
void Developer::sendPromotionRequest(double amount)
{
	if (this->getTeamLead() == nullptr)
	{
		return;
	}
	PromotionRequest promRequest(this->getName(), amount);
	this->getTeamLead()->addPromotionRequest(promRequest);
}