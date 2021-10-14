#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

unsigned int timesFoundChar(string word, char searchedChar)
{
    unsigned int times = 0;
    for (unsigned int i = 0; i < word.length(); ++i)
    {
        if (word[i] == searchedChar)
        {
            times++;
            continue;
        }
    }
    return times;
}


int main() {
    string word;
    int chars = 0;
    char searchedChar = '\0';

    cin >> word >> chars >> searchedChar;

    unsigned int remainder = (unsigned int)chars % word.length();
    unsigned int result = (unsigned int)((chars / word.length()) * timesFoundChar(word, searchedChar));
    for (unsigned int i = 0; i < remainder; ++i)
    {
        if (word[i] == searchedChar)
        {
            result += 1;
        }
    }

    std::cout << result << std::endl;
}