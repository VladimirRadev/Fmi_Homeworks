#include "SectionVotes.hpp"
void SectionVotes::fillSectionVotesVector(const int& party1Votes, const int& party2Votes, const int& party3Votes)
{
	this->sectionVotes.clear();
	std::pair<Party, int>party1(PARTY1, party1Votes);
	std::pair<Party, int>party2(PARTY2, party2Votes);
	std::pair<Party, int>party3(PARTY3, party3Votes);
	this->sectionVotes.push_back(party1);
	this->sectionVotes.push_back(party2);
	this->sectionVotes.push_back(party3);
}

SectionVotes::SectionVotes()
{
	this->fillSectionVotesVector(-1, -1, -1);
}
SectionVotes::SectionVotes(int party1Votes, int party2Votes, int party3Votes)
{
	this->fillSectionVotesVector(party1Votes, party2Votes, party3Votes);
}
const std::vector<std::pair<Party, int>>& SectionVotes::getSectionVotes()const
{
	return this->sectionVotes;
}
int SectionVotes::votesForParty(Party toCheck) const
{
	for (int i = 0; i < this->sectionVotes.size(); i++)
	{
		if (this->sectionVotes[i].first == toCheck)
		{
			return this->sectionVotes[i].second;
		}
	}
	return 0;
}
std::istream& operator>>(std::istream& in, SectionVotes& line)
{
	int party1votes = 0, party2votes = 0, party3votes = 0;
	in >> party1votes >> party2votes >> party3votes;
	line.fillSectionVotesVector(party1votes, party2votes, party3votes);
	return in;
}
std::ostream& operator<<(std::ostream& out, const SectionVotes& line)
{
	out << line.sectionVotes[0].second << ' ' << line.sectionVotes[1].second << ' ' << line.sectionVotes[2].second << '\n';
	return out;
}