/**
*
* Solution to homework assignment 1
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
#include <string>
using namespace std;
void validateData(long long& N, long long& X, 
	long long& M, short downLimitOfPossibleValues)
{
	while (true)
	{
		cin >> N;
		if (N > downLimitOfPossibleValues)
		{
			break;
		}
	}
	while (true)
	{
		cin >> X;
		if (X > downLimitOfPossibleValues)
		{
			break;
		}
	}
	while (true)
	{
		cin >> M;
		if (M > downLimitOfPossibleValues)
		{
			break;
		}
	}

}
int main()
{
	long long N = 0, X = 0, M = 0, totalMoneyOfChild = 0;
	const short DOWN_LIMIT_OF_POSSIBLE_NUMBERS = 0;
	const short MONEY_PRESENT_FOR_SECOND_BIRTHDAY = 30;
	const short TREAT_FOR_FRIENDS = 5;

	long long evenBirthdays = 1;
	validateData(N, X, M, DOWN_LIMIT_OF_POSSIBLE_NUMBERS);
	for (long long yearsOld = 1; yearsOld <= N; yearsOld++)
	{
	    //check for second birthday of mitko
		if (yearsOld == 2)
		{
			totalMoneyOfChild += MONEY_PRESENT_FOR_SECOND_BIRTHDAY;
			totalMoneyOfChild -= TREAT_FOR_FRIENDS;
			evenBirthdays++;
			continue;
		}
		if (yearsOld % 2 == 0)
		{
			totalMoneyOfChild += (evenBirthdays * MONEY_PRESENT_FOR_SECOND_BIRTHDAY);
			totalMoneyOfChild -= TREAT_FOR_FRIENDS;
			evenBirthdays++;
		}
		else if (yearsOld % 2 != 0)
		{
			totalMoneyOfChild += M;
		}
	}

	//if mitko spend more money than a prize of laptop
	//he can buy it
	if (totalMoneyOfChild >= X)
	{
		cout << "yes" << endl;
		cout << totalMoneyOfChild - X << endl;
	}
	else
	{
		cout << "no" << endl;
		cout << X - totalMoneyOfChild << endl;
	}
	
	

}