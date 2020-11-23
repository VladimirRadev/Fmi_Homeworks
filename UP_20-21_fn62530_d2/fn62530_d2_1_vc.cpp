/**
*
* Solution to homework assignment 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Vladimir Radev
* @idnumber 62530
* @task 1
* @compiler VC
*
*/
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
bool isNaturalNumber(long long inputNum)
{
	if (inputNum >= 1)
	{
		return true;
	}
	return false;
}

int main()
{
	const short DOWN_LIMIT_OF_N = 3;
	const short UP_LIMIT_OF_N = 100;
	int N = 0;
	long long inputNum = 0;
	cin >> N;
	vector<int>givenNumbers;

	while(N < DOWN_LIMIT_OF_N || N > UP_LIMIT_OF_N)
	{
		cin >> N;
	}
	while (N > 0 && (cin >> inputNum))
	{
		if (isNaturalNumber(inputNum))
		{
			givenNumbers.push_back(inputNum);
			N--;
		}
	}
	bool isTriangleSequence = true;

	//we start from first 2 elements and check if abs difference of last two element
	//isn't equal than an abs difference of first 2 elements
	//if it isn't equal then given sequance isn't triangle
	for (int i = 0,j=givenNumbers.size()-1; i < (givenNumbers.size()/2) &&
		j>(givenNumbers.size()/2); i++,j--)
	{
		int аbsDifferenceTwoNumbers = abs(givenNumbers[i] - givenNumbers[i + 1]);
		int mirrorAbsDifference = abs(givenNumbers[j] - givenNumbers[j-1]);
		if (mirrorAbsDifference != аbsDifferenceTwoNumbers)
		{
			isTriangleSequence = false;
			break;

		}
		


	}
	if (isTriangleSequence)
	{
		cout << 1 << endl;
	}
	else
		cout << 0 << endl;


}