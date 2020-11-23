/**
*
* Solution to homework assignment 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Vladimir Radev
* @idnumber 62530
* @task 3
* @compiler VC
*
*/
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

bool isPolindrom(vector<int>& numbersPolindrom)
{
	bool flag = true;
	int numbersPolindromSize = numbersPolindrom.size();
	for (int i = 0; i < (numbersPolindromSize/2); i++)
	{
		if (numbersPolindrom[i] != numbersPolindrom[numbersPolindromSize - 1 - i])
		{
			flag=false;
			break;
		}
	}
	return flag;
}
bool isDigit(int inputNum)
{
	if(inputNum>=0 && inputNum<=9)
	{
		return true;
	}
	return false;
}

int main()
{

	const short DOWN_LIMIT_OF_N = 3;
	const short UP_LIMIT_OF_N = 1000;
	const int MIN_LIMIT_USER_INPUT = INT_MIN;
	const int MAX_LIMIT_USER_INPUT = INT_MAX;
	int N = 0, inputNum = 0;
	cin >> N;
	vector<int>givenNumbers;

	while (N < DOWN_LIMIT_OF_N || N > UP_LIMIT_OF_N)
	{
		cin >> N;
	}
	while (N > 0 && (cin >> inputNum))
	{
		//check if inputNum is digit and it's possible value
		if (isDigit(inputNum))
		{
			givenNumbers.push_back(inputNum);
			N--;
		}
	}
	int polindromsCount = 0;

	//minimum polindrom's length is 3 so we should
	//looping till i <= vector.size() - 3
	for (int i = 0; i <= givenNumbers.size() - 3; i++)
	{
		vector<int>currentPolindrom;

		//we push every element of givenNumbers in currentPolindrom
		//to check if sequance of numbers in order user's input is
		//relevant polindrom
		currentPolindrom.push_back(givenNumbers[i]);


		for (int j = i + 1; j < givenNumbers.size(); j++)
		{
			currentPolindrom.push_back(givenNumbers[j]);



			//to have polindrom first element of currentPolindrom vector
			//should be the same as last and also currentPolindrom size
			//should be greater or equal than 3
			if ((givenNumbers[i] == givenNumbers[j]) && currentPolindrom.size() >= 3)
			{



				//function to check if sequance of elements of currentPolindrom's vector
				//in order they are added is polindrom
				if (isPolindrom(currentPolindrom))
				{
					polindromsCount++;
				}

			}


		}
		//if we went to the end so clear the currentPolindrom
		//and check with the next iteration of index i
		currentPolindrom.clear();
	}
	if (polindromsCount != 0)
	{
		cout << polindromsCount << endl;
	}
	else
		cout << "-1" << endl;


}