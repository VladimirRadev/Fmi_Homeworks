/**
*
* Solution to homework assignment 4
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
using namespace std;
int FindMax(int* arr, int M)
{
	int max = INT_MIN;
	for (int i = 0; i < M; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}
int LongestIncreacingSubsequance(int *arr, int M)
{
	int longestIncrSubArr[1000] = { 0 };
	//we will storage the size of longest increacing subsequance as value at index i
	//where the value will be determined of size of longest increascing subsequance of indexes before i
	//example: 10, 2 , 3, 1 -> lis[0]=1 ( arr[0]=10 and 10 is the first element in longestIncrSubArr[] so will be {10}->size=1)
	//longestIncrSubArr[1]=1 ( because arr[1]=2 is not greater than 10 so {2} is lis of this index)
	//longestIncrSubArr[2]=2 (because (arr[1]=2) <= (arr[2]=3) -> lis at index 2 = {2,3}->size=2)
	//longestIncrSubArr[3]=1(because arr[3]=1 is minimal element of arr -> lis at index 3={1})
	longestIncrSubArr[0] = 1;
	for (int i = 1; i < M; i++)
	{
		//we set at index i longestIncrSubArr[i]=1 because element by itself is also a lis
		longestIncrSubArr[i] = 1;
		for (int j = 0; j < i; j++)
		{
			//checking if element placed ahead (with index i) is greater or equal than element placed before it (with index j)
			//and also if longestIncrSubArr[j]( the value of lis at index j) + itself (arr[i]) is greater 
			//than the past value of longestIncrSubArr[i] then set a longestIncrSubArr[i] to a past value incremented + 1

			//example : 2,3,4 -> longestIncrSubArr[0]=1 because 2 by itself is lis (lis(arr[0])=lis(2)={2}->1)
			// longestIncrSubArr[1]= longestIncrSubArr[0] + itself(lis(arr[1])->{3}->1) = 1 + 1=2 (because 3 is greater than 2 )
			// longestIncrSubArr[2]
			//first step: longestIncrSubArr[0] + itself(lis(arr[2])->{4}->1) = 1 + 1 = 2 (because 4 is greater than 2 )
			//second step: longestIncrSubArr[1] + itself(lis(arr[2])->{4}->1) = 2 + 1 = 3 (because 4 is greater than 3 )
			if (arr[i] >= arr[j] && longestIncrSubArr[i] < longestIncrSubArr[j] + 1)
			{
				longestIncrSubArr[i] = longestIncrSubArr[j] + 1;
			}
		}
	}

	// we need to return the maximum element in longestIncrSubArr (or with other word the size of maximum lis found in given arr)
	return FindMax(longestIncrSubArr,M);
}
bool PossibleAscendingOrder(int* arr, int M, int N)
{
	//in case as : 10,1 ; 2,1; 1,1 (no matter what numbers are given with replacing one of it  with natural number
	//such as the order in the array to be ascending order, the function will allways returning true
	if (M <= 2 && N >= 1)
	{
		return true;
	}
	else
	{
		//the solution of task is to find the size of longest increacing subsequance (lis) of elements in given arr
		//without shifting position and also set the values of elements which are not in this lis
		//to a values belong to this lis with this operation distract one of possible changes( N--).
		//We are able to use N changes if we  use more (or with other word if M(=size of arr) - lis.size() > N) 
		//then the function will return false

		//example: 10 3 1 1 1 -> lis={1,1,1} but {10,3} aren't inside lis, so -> set {10,3} to {1,1}
		//if we own N>=2 ( 2 is the number of changes 10->1 and 3->1) then the function will return true
		//or else we own only one change then the funciton will return false
		int lis = LongestIncreacingSubsequance(arr, M);

		if (M - lis <= N)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	
}
int main()
{


	const int MIN_VALUE_FOR_NATURAL_INTEGER = 1;
	long long N = 0, M = 0;
	cin >> N;
	if (N < MIN_VALUE_FOR_NATURAL_INTEGER)
	{
		cout << "-1" << endl;
		return 0;
	}
	cin >> M;
	//if M<=N we can't change more items than we have
	if (M < MIN_VALUE_FOR_NATURAL_INTEGER || M<=N)
	{
		cout << "-1" << endl;
		return 0;
	}
	int* arr = new int[M];
	for (int i = 0; i < M; i++)
	{
		int input = 0;
		cin >> input;
		if (input < MIN_VALUE_FOR_NATURAL_INTEGER)
		{
			cout << "-1" << endl;
			return 0;
		}
		else
		{
			arr[i] = input;
		}
	}
	cout << PossibleAscendingOrder(arr, M, N)<<endl;
	delete[]arr;
}