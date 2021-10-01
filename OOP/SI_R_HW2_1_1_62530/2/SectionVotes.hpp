#pragma once
#include <vector>
#include <utility>
#include <fstream>

enum Party
{
    PARTY1 = 0,
    PARTY2 = 1,
    PARTY3 = 2,
};

class SectionVotes
{
private:
    std::vector<std::pair<Party, int>>sectionVotes;
    void fillSectionVotesVector(const int& party1Votes, const int& party2Votes, const int& party3Votes);
public:
    SectionVotes();
    SectionVotes(int party1Votes, int party2Votes, int party3Votes);

    const std::vector<std::pair<Party, int>>& getSectionVotes()const;
    int votesForParty(Party) const;
    
    friend std::istream& operator>>(std::istream& in, SectionVotes& line);
    friend std::ostream& operator<<(std::ostream& out, const SectionVotes& line);

};
