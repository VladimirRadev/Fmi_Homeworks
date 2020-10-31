/**
*
* Solution to homework assignment 1
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

using namespace std;
void validateData(long long& inputNum, short downLimitOfPossibleValues)
{
	while (true)
	{
		cin >> inputNum;
		if (inputNum > downLimitOfPossibleValues)
		{
			break;
		}
	}
}
int main()
{
	const short DOWN_LIMIT_OF_POSSIBLE_NUMBERS = 0;
	long long inputNum=0, maximumNum=0,secondMaximumNum=0;
	int iterator = 0;
	validateData(inputNum, DOWN_LIMIT_OF_POSSIBLE_NUMBERS);
	while (inputNum>0)
	{
		//inizialization of first input num
		//we set maximumNum to inputNum also
		//secondMaximumNum to inputNum
		if (iterator==0)
		{
			maximumNum = inputNum;
			secondMaximumNum = inputNum;
			iterator++;
			cin >> inputNum;
			continue;
		}

		//we set a maximumNum to an inputNum and
		//also secondMaximum to a last maximumNum
		if (inputNum > maximumNum)
		{
			secondMaximumNum = maximumNum;
			maximumNum = inputNum;
			continue;
		}

		//if inputNum is bigger than last secondMaximumNum
		//but lower than maximumm num we set
		//inputNum to a new secondMaximumNum
		else if (inputNum<maximumNum && inputNum>secondMaximumNum)
		{
			secondMaximumNum = inputNum ;
		}

		//if user type for example: 3 1
		//we haven't change a secondMaximumNum already so if 
		//inputNum is lower than maximumNum(also secondMaximum because 
		//they are equal at first iteration) we set inputNum to a new secondMaximumNum
		else if (secondMaximumNum == maximumNum && inputNum < maximumNum)
		{
			secondMaximumNum = inputNum;
		}
		cin >> inputNum;
	}

	//if secondMaximumNum is not changed so we have one of these cases:
	//1 0 -> -1 , 1 1 1 1 -> -1
	if (secondMaximumNum == maximumNum)
	{
		cout << "-1" << endl;
		return 0;
	}
	cout << secondMaximumNum << endl;
}