/**
*
* Solution to homework assignment 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Vladimir Radev
* @idnumber 62530
* @task 5
* @compiler VC
*
*/

#include <iostream>
#include <string>
#include <cmath>


using namespace std;
void validateData(long long& inputNum, short downLimitOfPossibleValues,
	long long upperLimitOfPossibleValues)
{
	while (true)
	{
		cin >> inputNum;
		if (inputNum >= downLimitOfPossibleValues && inputNum <= upperLimitOfPossibleValues)
		{
			break;
		}
	}

}

int main()
{
	const short NUMBER_ONE = 1;
	const short MIN_VALUE_OF_GIVEN_NUMBER = 2;
	const long long MAX_VALUE_OF_GIVEN_NUMBER = pow(10, 9);
    long long inputNum = 0, copyOfInputNum = 0;

	validateData(inputNum, MIN_VALUE_OF_GIVEN_NUMBER, MAX_VALUE_OF_GIVEN_NUMBER);
	copyOfInputNum = inputNum; 

	//check if all dividers of inputNum are two or five
	while (inputNum % 2 == 0)
	{
		inputNum /= 2;
	}
	while (inputNum % 5 == 0)
	{
		inputNum /= 5;
	}
	//if it has a different divider from 2 or 5
	//the fraction 1/n is endless
	if (inputNum != 1)
	{
		cout << "NO" << endl;
		return 0;
	}
	inputNum = copyOfInputNum;
	double fraction = NUMBER_ONE / (double)inputNum;
	int countOfDigitAfterDecimalPoint = 0;

	//while fraction is number with floating point
	//multiply it with 10, after еxecution of the while loop
	//we have a counter of digits after decimal point
	while (fraction != (int)fraction)
	{
		fraction *= 10;
		countOfDigitAfterDecimalPoint++;
	}
	cout << countOfDigitAfterDecimalPoint << endl;

}