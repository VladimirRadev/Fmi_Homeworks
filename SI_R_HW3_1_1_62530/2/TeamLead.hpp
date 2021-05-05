#pragma once
#include <string>
#include <vector>
#include "Developer.hpp"
#include "LeavingRequest.hpp"
#include "PromotionRequest.hpp"

class TeamLead:public Developer
{
private:
	std::vector<Developer*>team;
	std::vector<LeavingRequest>leavingRequests;
	std::vector<PromotionRequest>promotionRequests;
public:
	TeamLead(const std::string& name, const double& salary);
	~TeamLead()override;
	std::vector<Developer*> getTeam()const;
	void addDeveloperToTeam(Developer* developer, double salary);
	void removeDeveloperFromTeam(const std::string& name);
	void increaseTeamSalariesBy(double amount);
	void decreaseTeamSalariesBy(double amount);
	void addLeavingRequest(const LeavingRequest& leavingRequest);
	void addPromotionRequest(const PromotionRequest& promotionRequest);
	void fulfillLeavingRequests();
	void fulfillPromotionRequests();
};