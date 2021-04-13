#pragma once
#include "SectionVotes.hpp"
#include <fstream>
#include <vector>
class ElectionResultsDatabase
{
private:
    std::vector<SectionVotes>resultsFromSections;
public:

    void addResultsFromFile(const char* filename);

    int numberOfSections() const;

    int votesForParty(Party) const;

    Party winningParty() const;

    friend std::istream& operator>>(std::istream& in, ElectionResultsDatabase& database);
    friend std::ostream& operator<<(std::ostream& out, const ElectionResultsDatabase& database);
};