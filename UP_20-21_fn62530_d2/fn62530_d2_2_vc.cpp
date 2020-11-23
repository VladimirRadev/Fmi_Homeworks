/**
*
* Solution to homework assignment 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Vladimir Radev
* @idnumber 62530
* @task 2
* @compiler VC
*
*/
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

bool isOrderByDescendingOrEqual(vector<double>& numsToCheck)
{
	bool flag = true;
	for (int i = 0; i < numsToCheck.size() - 1 ; i++)
	{
		if (numsToCheck[i] >= numsToCheck[i + 1])
		{
			continue;
		}
		flag = false;
	}
	return flag;
}
bool isOrderedSequance(vector<double>& numToCheck)
{
	bool flag = true;
	for (int i = 0; i < numToCheck.size() - 1; i++)
	{
		if (numToCheck[i] < numToCheck[i + 1])
		{
			continue;
		}
		flag = false;
	}
	return flag;
}
double greaterAmountOfWinnigs(vector<double>& combinationNumbers)
{
	if (combinationNumbers.empty())
	{
		return 0.0;
	}

	//selection sort
	for (int i = 0; i < combinationNumbers.size() - 1; i++)
	{
		int indexMaxNum = i;
		for (int j = i + 1;  j < combinationNumbers.size();  j++)
		{
			if (combinationNumbers[indexMaxNum]< combinationNumbers[j])
			{
				indexMaxNum = j;
			}

		}
		double temp = combinationNumbers[i];
		combinationNumbers[i] = combinationNumbers[indexMaxNum];
		combinationNumbers[indexMaxNum] = temp;
		
	}
	return combinationNumbers[0];
}

int main()
{

	const short DOWN_LIMIT_OF_N = 3;
	const short UP_LIMIT_OF_N = 365;
	const double MIN_LIMIT_USER_INPUT = 0.1;
	const double MAX_LIMIT_USER_INPUT = 100.0;
	int N = 0;
	double inputNum = 0.0;
	cin >> N;
	vector<double>givenNumbers;

	while (N < DOWN_LIMIT_OF_N || N > UP_LIMIT_OF_N)
	{
		cin >> N;
	}
	while (N > 0 && (cin >> inputNum))
	{
		if (inputNum >= MIN_LIMIT_USER_INPUT && inputNum <= MAX_LIMIT_USER_INPUT)
		{
			givenNumbers.push_back(inputNum);
			N--;
		}
	}
	double maxMoneyIncome = 0.0;

	//if givenNumbers are ordered so maxMoneyIncome would be
	//price of highest stock minus price of lower stock's price
	if (isOrderedSequance(givenNumbers))
	{
		cout << abs(givenNumbers[0] - givenNumbers[givenNumbers.size() - 1])<<endl;
		return 0;
	}

	//if givenNumbers are OrderByDescendingOrEqual so we wouldn't
	//make profit with prices of stocks
	if (isOrderByDescendingOrEqual(givenNumbers))
	{
		cout << 0 << endl;
		return 0;
	}

	//in every other case
	for (int i = 0; i < givenNumbers.size() - 1 ; i++)
	{
		vector<double>currentPossibleCombinations;
		int indexmaxNumInSubsequance = i+1;

		//we trying to find highest stock price in the future days
		//and buy the stock with the lower price in last days
		while (i < indexmaxNumInSubsequance)
		{
			for (int j = i + 1; j < givenNumbers.size(); j++)
			{
				//if we are at last day and didn't find stock's price drop
				//and the price are higher or equal than the day before last day
				//so we should push it in currentPossibleCombinations
				if (j + 1 == givenNumbers.size())
				{

					//if we are at the end we want to break while with i++
					//and push the possible combination in vector
					if (givenNumbers[i]<givenNumbers[j] && givenNumbers[j]>=givenNumbers[j - 1])
					{
						currentPossibleCombinations.
							push_back(abs(givenNumbers[i] - givenNumbers[j]));
						indexmaxNumInSubsequance = j;
						i++;
						continue;
					}
					i++;
					break;
				}
				//we are finding stock's price drop se we would have maximum profit
				//example: 1 2 3 4 3 2
				//highest stock price is 4 so we checking every possible combinations
				//of sold highest stock price (4) with bought stock in the days before(1,2,3)
				if (givenNumbers[i]<givenNumbers[j] && givenNumbers[j]>givenNumbers[j + 1])
				{
					currentPossibleCombinations.
						push_back(abs(givenNumbers[i] - givenNumbers[j]));
					indexmaxNumInSubsequance = j;
					i++;
					break;


				}
			}
		}
		//we order currentPosibleCominations vector so first element will be highest
		//and sum it with maxMoneyIncome, then clear the currentPosiibleCombinations vector
		maxMoneyIncome += greaterAmountOfWinnigs(currentPossibleCombinations);
		currentPossibleCombinations.clear();

	}
	cout << maxMoneyIncome << endl;


}