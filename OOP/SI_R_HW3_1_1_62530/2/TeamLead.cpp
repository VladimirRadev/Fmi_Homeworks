#include "TeamLead.hpp"
TeamLead::TeamLead(const std::string& name, const double& salary) :Developer(name)
{
	this->setTeamLead(this);
	this->setInitialSalary(salary);
}
TeamLead::~TeamLead()
{
	while (!this->team.empty())
	{
		this->team[0]->setTeamLead(nullptr);
		this->team.erase(this->team.begin() + 0);
	}
	this->leavingRequests.clear();
	this->promotionRequests.clear();
	//this->setTeamLead(nullptr);
}
std::vector<Developer*> TeamLead::getTeam()const
{
	return team;
}
void TeamLead::addDeveloperToTeam(Developer* developer, double salary)
{
	if (developer == nullptr)
	{
		return;
	}
	developer->setInitialSalary(salary);
	developer->setTeamLead(this);
	this->team.push_back(developer);
}
void TeamLead::removeDeveloperFromTeam(const std::string& name)
{
	for (int i = (this->team.size() - 1); i >= 0; --i)
	{
		if (this->team[i]->getName() == name)
		{
			this->team[i]->setTeamLead(nullptr);
			this->team.erase(this->team.begin() + i);
			break;
		}
	}
	return;
}
void TeamLead::increaseTeamSalariesBy(double amount)
{
	for (long unsigned int i = 0; i < this->team.size(); i++)
	{
		this->team[i]->setSalary(this->team[i]->getSalary() + amount);
	}
	return;
}
void TeamLead::decreaseTeamSalariesBy(double amount)
{
	for (long unsigned int i = 0; i < this->team.size(); i++)
	{
		this->team[i]->setSalary(this->team[i]->getSalary() - amount);
	}
	return;
}
void TeamLead::addLeavingRequest(const LeavingRequest& leavingRequest)
{
	this->leavingRequests.push_back(leavingRequest);
}
void TeamLead::addPromotionRequest(const PromotionRequest& promotionRequest)
{
	this->promotionRequests.push_back(promotionRequest);
}
void TeamLead::fulfillLeavingRequests()
{
	for (long unsigned int i = 0; i < this->leavingRequests.size(); i++)
	{
		std::string leavingPersonName = this->leavingRequests[i].getSender();
		this->removeDeveloperFromTeam(leavingPersonName);
	}
	this->leavingRequests.clear();
}
void TeamLead::fulfillPromotionRequests()
{
	for (long unsigned int i = 0; i < this->promotionRequests.size(); i++)
	{
		std::string developerToPromote = this->promotionRequests[i].getSender();
		double amount = this->promotionRequests[i].getAmount();
		for (long unsigned int i = 0; i < this->team.size(); i++)
		{
			if (this->team[i]->getName() == developerToPromote)
			{
				this->team[i]->setSalary(this->team[i]->getSalary() + amount);
				break;
			}
		}
	}
	this->promotionRequests.clear();
}