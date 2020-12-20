/**
*
* Solution to homework assignment 3
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

//we use MAX_STR_SIZE as global variable because we using it
//in more than one function and would be not practical if every
//function takes it as argument in its declaration
const int MAX_STR_SIZE = 1000;

int SizeOfStr(char* str)
{
	int lengthOfStr = 0;
	//every string ends with NULL termination character
	while (*(str + lengthOfStr) != '\0')
	{
		++lengthOfStr;
	}
	return lengthOfStr;
}
bool ContainsStr(char checkedSymbols[], char check)
{
	int lengthOfCheckedSymbols = SizeOfStr(checkedSymbols);
	for (int i = 0; i < lengthOfCheckedSymbols; i++)
	{
		//if char check contains in checkedSymbols array 
		//then return true
		if (check == checkedSymbols[i])
			return true;

	}
	return false;
}
bool EqualArray(int arr[], int arraySize)
{
	int toCheck = arr[0];
	for (int i = 1; i < arraySize; i++)
	{
		//check if array of integers is equal
		//example: 1 1 1 1 -> true
		if (toCheck != arr[i])
			return false;
			
	}
	return true;

}
bool PossibleDeleteOfElement(int arr[],int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		bool flag = true;
		//substract one from each element in arr and check 
		//if this element substract from and  other element are equal
		//{3,2} -> ? {2,2} -> true
		int subtractOne = arr[i] - 1;
		//if subtractOne is one it means arr has a element contais in it once
		//{abb} -> {1,2} -> 'a' contains once
		if (subtractOne == 0)
		{
			int copyOfarr[MAX_STR_SIZE] = {}, copyOfarrSize=0;

			//copy all elements of arr in copyOfarr excluding arr[i]
			for (int q = 0; q < arraySize; q++)
			{
				if (q == i)
				{
					continue;
				}
				copyOfarr[copyOfarrSize++] = arr[q];

			}
			//if elements in copyOfarr are equal then 
			//substraction one from arr[i] is possible and return true
			if (EqualArray(copyOfarr, copyOfarrSize))
			{
				return true;
			}
		}
		//in other cases if subtractOne isn't zero or with other words
		//arr[i] isn't 1. then check other elents of arr excluding subtractOne are equal
		//each other. example : {2,3,2,3,3} we substract one from 3(pos 1)
		//but {2,2,2,3,3} are not equal sequance -> false
		for (int k = 0; k < arraySize; k++)
		{
			if (k == i)
				continue;
			if (subtractOne == arr[k])
			{
				continue;
			}
			flag = false;
			break;
		}
		if (flag == true)
			return true;


	}
	return false;
}
bool IsCorrectString(char str[])
{
	int lengthOfStr = SizeOfStr(str);
	//we will store already checked symbols of str in checkedSymbols arr
	char checkedSymbols[MAX_STR_SIZE] = {};

	//we should know also count of every unique char which was checked already 
    //example: aabbb -> uniqueCharCount={2,3};
	int uniqueCharCount[MAX_STR_SIZE] = { 0 };
	int checkedSymbolsSize = 0, uniqueCharCountSize=0;
	for (int i = 0; i < lengthOfStr; i++)
	{
		//if current char( str[i]) doesn't contains in checkedSymbols
		//then add it to checkedSymbols, if does then just continue with next iteration
		if (!ContainsStr(checkedSymbols, str[i]))
		{
			checkedSymbols[checkedSymbolsSize++] = str[i];
			int currentCount = 1;

			//for loop to calculate count of just added
			//unique char placed in checkedSymbols arr
			for (int j = i + 1; j < lengthOfStr; j++)
			{
				if (str[i] == str[j])
				{
					currentCount++;

				}
			}
			//we should know also count of every unique char which was checked already 
	        //example: aabbb -> uniqueCharCount={2,3};
			uniqueCharCount[uniqueCharCountSize++] = currentCount;
		}
	}
	//if we could subtract 1 from single element of uniqueCharCount arr
	//or elements of uniqueCharCount are equal then return true
	//example: aaabb -> {3,2} -> {3-1=2,2} -> 2==2 -> true
	if (PossibleDeleteOfElement(uniqueCharCount, uniqueCharCountSize)
		|| EqualArray(uniqueCharCount, uniqueCharCountSize))
	{
		return true;
	}
	return false;
}
int main()
{
	char str[MAX_STR_SIZE];
	int lengthOfStr = -1;
	do
	{
		cin >> str;
		lengthOfStr = SizeOfStr(str);
	} while (lengthOfStr <= 0 || lengthOfStr > 150);
	cout << IsCorrectString(str) << endl;

}