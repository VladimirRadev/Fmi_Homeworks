#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	unsigned int n = 0;
	cin >> n;

	vector<char>numbers;
	vector<char>smallLetters;
	vector<char>bigLetters;

	string word;
	cin >> word;
	for (long unsigned int i = 0; i < n; i++)
	{
		if (word[i] >= 48 && word[i] <= 57)
		{
			numbers.push_back(word[i]);
			continue;
		}
		//'a'-'z'
		else if (word[i] >= 97 && word[i] <= 122)
		{
			smallLetters.push_back(word[i]);
			continue;
		}
		//'A'-'Z'
		else if (word[i] >= 65 && word[i] <= 90)
		{
			bigLetters.push_back(word[i]);
			continue;
		}
		else {
			continue;
		}

	}

	sort(numbers.begin(), numbers.end());
	sort(smallLetters.begin(), smallLetters.end());
	sort(bigLetters.begin(), bigLetters.end());

	for (long unsigned int  i = 0; i < numbers.size(); i++)
	{
		cout << numbers[i];
	}
	for (long unsigned int i = 0; i < smallLetters.size(); i++)
	{
		cout << smallLetters[i];
	}
	for(long unsigned int i = 0; i < bigLetters.size(); i++)
	{
		cout << bigLetters[i];
	}
	cout << endl;

}

