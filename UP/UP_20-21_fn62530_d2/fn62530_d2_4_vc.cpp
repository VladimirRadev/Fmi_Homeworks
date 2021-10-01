/**
*
* Solution to homework assignment 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Vladimir Radev
* @idnumber 62530
* @task 4
* @compiler VC
*
*/
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{

	const short DOWN_LIMIT_OF_N = 3;
	const short UP_LIMIT_OF_N = 100;
	const int MIN_LIMIT_USER_INPUT = INT_MIN;
	const int MAX_LIMIT_USER_INPUT = INT_MAX;

	int N = 0;
	long long inputNum = 0;
	cin >> N;
	vector<int>givenNumbers;

	//ask user for input while N is in possible range
	while (N < DOWN_LIMIT_OF_N || N > UP_LIMIT_OF_N)
	{
		cin >> N;
	}
	while (N > 0 && (cin >> inputNum))
	{
		//if inputNum is in possible range we should check if its distinct
		if (inputNum >= MIN_LIMIT_USER_INPUT && inputNum <= MAX_LIMIT_USER_INPUT)
		{
			//if vector isEmpty and hasn't elements inside we push first correct element
			if (givenNumbers.empty())
			{
				givenNumbers.push_back(inputNum);
				N--;
				continue;
			}
			bool flag = true;

			//check if inputNum already exists in our vector
			//if do then ask user for new input
			for (int i = 0; i < givenNumbers.size(); i++)
			{
				if (inputNum == givenNumbers[i])
				{
					flag = false;
					break;
				}
			}
			
			//if doesn't then push it back in the vector
			if (flag)
			{
				givenNumbers.push_back(inputNum);
				N--;
				continue;
			}
		}
		
	}
	int sumOfThreeRandomNumbersIsZero = 0;

	//we should check every combinations of three
	//random nums, which sum is zero.
	//The way we make it is with taking one number and combinate it
	//with every couple numbers till end of the vector
	//for example: 0 1 2 3 -3 2
	//we take 0 and trying with 1 2; 1 3 ; 1 -3 and so...
	for (int i = 0; i <= givenNumbers.size() - 3; i++)
	{
		//we starting with next index because we already check last one
		for (int j = i + 1; j <= givenNumbers.size() - 2; j++)
		{
			//we starting with next index because we already check last one
			for (int k = j + 1; k <= givenNumbers.size() - 1; k++)
			{
				//if we have distinct combinataion of three numbers giving zero
				//we add 1 to our counter
				if ((givenNumbers[k] + givenNumbers[j] + givenNumbers[i]) == 0)
				{
					sumOfThreeRandomNumbersIsZero++;
				}
			}

		}

	}
	cout << sumOfThreeRandomNumbersIsZero << endl;


}