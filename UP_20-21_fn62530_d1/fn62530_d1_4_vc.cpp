/**
*
* Solution to homework assignment 1
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
#include <string>
#include <cmath>

using namespace std;

bool isPrime(long long num)
{
	
	for (long long  i = 2; i <= num/2; i++)
	{
		if (num % i == 0)
		{
			return false;
		}

	}
	return true;
}
void findTwoDividersWithMinimumSumOfNumAndOrderThem(long long num,
    long long& firstMultiplyer,
	long long& secondMultiplyer)
{
	if (num <= 3 && num >= 1)
	{
		firstMultiplyer = 1;
		secondMultiplyer = num;
		return;
	}
	long long i = 1, k = 1,minSum=INT_MAX;
	for (i = 1; i <= k; i++)
	{
		if (num % i == 0)
		{
			for (k = (num/i); k <= num; k++)
			{
				if ((i * k) == num && (i + k) < minSum)
				{
					firstMultiplyer = i;
					secondMultiplyer = k;
					minSum = (i + k);
					break;
				}
				k = num;
				break;

			}
		}

	}
	
}
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


	const short MIN_VALUE_OF_GIVEN_NUMBER = 1;
	const long long MAX_VALUE_OF_GIVEN_NUMBER = pow(10, 9);
	long long inputNum = 0;

	validateData(inputNum, MIN_VALUE_OF_GIVEN_NUMBER, MAX_VALUE_OF_GIVEN_NUMBER);
	
	long long i = 1, k = 1, j = 1;

	long long firstMultiplier = 1, thirdMultiplier = 1,
		secondMultiplier = 1, minSum= INT_MAX;
	for (i = 1; i <= thirdMultiplier && i<=secondMultiplier ; i++)
	{
		//we want multipliers to be ordered like that: 
		//firstMultiplier >= secondMultiplier >= thirdMultiplier 
		//so we got faster performance because we don't check 
		//next iterations of for loop
		if (i > k)
		{
			break;
		}
		if (inputNum % i == 0)
		{
			for (k = i; k <= (inputNum / i); k++)
			{
				//we want multipliers to be ordered like that: 
				//firstMultiplier >= secondMultiplier >= thirdMultiplier 
				//so we got faster performance because we don't check 
				//next iterations of for loop
				if (k > j)
				{
					break;
				}
				

				//checking if k is one of the deviders by inputNum
				//if it's not go to next iteration
				if (inputNum % k == 0)
				{
					for (j = (inputNum/(i*k)); j <= (inputNum / (k * i)); j++)
					{
						//when i,k are dividers by inputNum but j is not
						//so it's useless to go down and check next if
						if ((i * k * j) < inputNum)
						{
							break;
						}

						//if j is prime and k<=j that means j is higher possible
						//devider of inputNum and also is prime so that we should
						//find first multiplyer and second multiplyer and print them
						//with a functiion findTwoDividersWithMinimumSumOfNumAndOrderThem()
						if (isPrime(j) && k<=j)
						{
							thirdMultiplier = j;
							findTwoDividersWithMinimumSumOfNumAndOrderThem((k*i), firstMultiplier,
								secondMultiplier);
							cout << firstMultiplier
								<< " " << secondMultiplier
								<< " " << thirdMultiplier << endl;
							return 0;

						}
						if (((i * k * j) == inputNum) && (k + i + j < minSum))
						{
							firstMultiplier = i;
							secondMultiplier = k;
							thirdMultiplier = j;
							minSum = (i + k + j);
							break;
						}

						//if we are here, we set k to inputNum
						//just to break a check on second for
						//and goes to next i ( i++ first for)
						k= inputNum;
						break;
						
					}
				}
			}
		}

	}
	cout << firstMultiplier 
		<< " " << secondMultiplier 
		<<" " << thirdMultiplier << endl;
}