#include "ElectionResultsDatabase.hpp"
void ElectionResultsDatabase::addResultsFromFile(const char* filename)
{
	std::ifstream inFile;
	inFile.open(filename, std::ios::in);
	if (!inFile)
	{
		return;
	}
	SectionVotes votesFromSection;
	while (inFile >> votesFromSection)
	{
		this->resultsFromSections.push_back(votesFromSection);
	}
	inFile.close();
}
int ElectionResultsDatabase::numberOfSections() const
{
	return this->resultsFromSections.size();
}
int ElectionResultsDatabase::votesForParty(Party partyToCheck) const
{
	int result = 0;
	for (int i = 0; i < this->resultsFromSections.size(); i++)
	{
		result += this->resultsFromSections[i].votesForParty(partyToCheck);
	}
	return result;
}
Party ElectionResultsDatabase::winningParty() const
{
	int party1 = this->votesForParty(PARTY1);
	int party2 = this->votesForParty(PARTY2);
	int party3 = this->votesForParty(PARTY3);
	std::vector < std::pair<Party, int>>electionResultsForAParty;
	electionResultsForAParty.push_back(std::pair<Party, int>(PARTY1, party1));
	electionResultsForAParty.push_back(std::pair<Party, int>(PARTY2, party2));
	electionResultsForAParty.push_back(std::pair<Party, int>(PARTY3, party3));
	for (int i = 0; i < electionResultsForAParty.size(); i++)
	{
		int j = i;
		while (j > 0)
		{
			if (electionResultsForAParty[j].second > electionResultsForAParty[j - 1].second)
			{
				std::pair<Party, int> temp = electionResultsForAParty[j - 1];
				electionResultsForAParty[j - 1] = electionResultsForAParty[j];
				electionResultsForAParty[j] = temp;
			}
			--j;
		}
	}
	if((electionResultsForAParty[0].second==electionResultsForAParty[1].second)
		&& (electionResultsForAParty[1].second == electionResultsForAParty[2].second))
	{
		return PARTY1;
	}
	if ((electionResultsForAParty[0].second == electionResultsForAParty[1].second)
		&& (electionResultsForAParty[1].second != electionResultsForAParty[2].second))
	{
		if (electionResultsForAParty[0].first > electionResultsForAParty[1].first)
		{
			return electionResultsForAParty[1].first;
		}
		else
		{
			return electionResultsForAParty[0].first;
		}
	}
	else
	{
		return electionResultsForAParty[0].first;
	}
}
std::istream& operator>>(std::istream& in, ElectionResultsDatabase& database)
{
	SectionVotes votesFromSection;
	while (in >> votesFromSection)
	{
		database.resultsFromSections.push_back(votesFromSection);
	}
	return in;
}
std::ostream& operator<<(std::ostream& out, const ElectionResultsDatabase& database)
{
	for (int i = 0; i < database.resultsFromSections.size(); i++)
	{
		out << database.resultsFromSections[i].getSectionVotes()[0].second << ' '
			<< database.resultsFromSections[i].getSectionVotes()[1].second << ' '
			<< database.resultsFromSections[i].getSectionVotes()[2].second << '\n';
	}
	return out;

}