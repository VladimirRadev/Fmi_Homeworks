/**
*
* Solution to homework assignment 1
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
#include <string>
using namespace std;


unsigned short countTimesContainZero(unsigned short firstNum, unsigned short secondNum
	, unsigned short thirdNum)
{
	unsigned short count = 0;
	if (firstNum == 0)
	{
		count++;
	}
	if (secondNum == 0)
	{
		count++;
	}
	if (thirdNum == 0)
	{
		count++;
	}
	return count;

}




unsigned short elementExceptZero(unsigned short firstNum,
	unsigned short secondNum,
	unsigned short thirdNum)
{
	unsigned short differentElementOfZero = 0;
	if (firstNum != 0)
	{
		differentElementOfZero = firstNum;
		return differentElementOfZero;
	}
	if (secondNum != 0)
	{
		differentElementOfZero = secondNum;
		return differentElementOfZero;
	}
	if (thirdNum != 0)
	{
		differentElementOfZero = thirdNum;
		return differentElementOfZero;
	}
	return differentElementOfZero;


}




bool isDigit(short num)
{
	if (num >= 0 && num <= 9)
	{
		return true;
	}
	return false;
}

void orderElements(unsigned short firstNum,
	unsigned short secondNum,
	unsigned short thirdNum,
	unsigned short &bigger,
	unsigned short &mid,
	unsigned short &lower)
{
	if (firstNum >= secondNum && firstNum >= thirdNum)
	{
		bigger = firstNum;
		if (secondNum >= thirdNum)
		{
			mid = secondNum;
			lower = thirdNum;
		}
		else
		{
			mid = thirdNum;
			lower = secondNum;
		}
	
	}
	else if (secondNum >= firstNum && secondNum >= thirdNum)
	{
		bigger = secondNum;
		if (firstNum >= thirdNum)
		{
			mid = firstNum;
			lower = thirdNum;
		}
		else
		{
			mid = thirdNum;
			lower = firstNum;
		}
	}
	else if (thirdNum >= firstNum && thirdNum >= secondNum)
	{
		bigger = thirdNum;
		if (firstNum > secondNum)
		{
			mid = firstNum;
			lower = secondNum;
		}
		else
		{
			mid = secondNum;
			lower = firstNum;
		}
	}

}


void validateData(short & firstNum, short& secondNum,
	short& thirdNum, short downLimitOfPossibleValues)
{
	while (true)
	{
		cin >> firstNum;
		if (firstNum >=downLimitOfPossibleValues && isDigit(firstNum) )
		{
			break;
		}
	}
	while (true)
	{
		cin >> secondNum;
		if (secondNum >= downLimitOfPossibleValues && isDigit(secondNum) )
		{
			break;
		}
	}
	while (true)
	{
		cin >> thirdNum;
		if (thirdNum >= downLimitOfPossibleValues && isDigit(thirdNum) )
		{
			break;
		}
	}

}

int main()
{
	const short DOWN_LIMIT_OF_POSSIBLE_NUMBERS = 0;
	short firstNum = 0, secondNum = 0, thirdNum = 0;
	int polindrom = 0;
	validateData(firstNum, secondNum, thirdNum, DOWN_LIMIT_OF_POSSIBLE_NUMBERS);

	//when 3 input nums are equal
	if (firstNum == secondNum && secondNum == thirdNum)
	{
		//check if any of them is zero
		if (firstNum == 0)
		{
			cout << '0' << endl;
			return 0;
		}
		polindrom = (firstNum * 100) + (secondNum * 10) + (thirdNum);
		cout << polindrom;
		return 0;
	}


	//when we have two equal nums a a c ||  a b b || a c c
	else if ((firstNum == secondNum) || (firstNum == thirdNum) || (secondNum == thirdNum))
	{
		unsigned short biggerNum = 0, mid = 0, lowerNum = 0;

		//order a elements by value and initialize them
		//in 3 variables (biggerNum,mid,lowernum)
		orderElements(firstNum, secondNum, thirdNum, biggerNum, mid, lowerNum);

		//check if some of them are zero
		unsigned short count = countTimesContainZero(firstNum, secondNum, thirdNum);

		//example 6 0 6 -> 606
		if (count == 1)
		{
			unsigned short elementDifferentThan0 = elementExceptZero(firstNum,
				secondNum, thirdNum);
			polindrom = (elementDifferentThan0 * 100) + elementDifferentThan0;
			cout << polindrom << endl;
			return 0;
		}

		//example 0 0 6 ->6006 
		//because we can't start with zero
		else if (count == 2)
		{
			unsigned short elementDifferentThan0 = elementExceptZero(firstNum,
				secondNum, thirdNum);
			polindrom = (elementDifferentThan0 * 1000) + elementDifferentThan0;
			cout << polindrom << endl;
			return 0;
		}

		//in every other case
		polindrom = (lowerNum * 10000) + (mid * 1000)
			+ (biggerNum * 100) + (mid * 10) + lowerNum;
		cout << polindrom << endl;
		return 0;
		


	}
	// if numbers are not equal -> a b c
	else if(firstNum!=secondNum&& firstNum!=thirdNum)
	{
		unsigned short biggerNum = 0, mid = 0, lowerNum = 0;

		//order a elements by value and initialize them
		//in 3 variables (biggerNum,mid,lowernum)
		orderElements(firstNum, secondNum, thirdNum, biggerNum, mid, lowerNum);

		//check if one of them is zero
		unsigned short count = countTimesContainZero(firstNum, secondNum, thirdNum);

		//if we have actually a zero among them
		if (count == 1)
		{
			polindrom = (mid * 10000) + (biggerNum * 100) + mid;
			cout << polindrom << endl;
			return 0;
		}

		//in every other case
		polindrom = (lowerNum * 10000) + (mid * 1000)
			 + (biggerNum * 100) + (mid * 10) + lowerNum;
		cout << polindrom << endl;
	}


}