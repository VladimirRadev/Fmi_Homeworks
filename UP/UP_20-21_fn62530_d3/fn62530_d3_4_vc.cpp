/**
*
* Solution to homework assignment 3
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
#include <malloc.h>
using namespace std;

//we use MAX_SIZE_STRING as global variable because we using it
//in more than one function and would be not practical if every
//function takes it as argument in its declaration
const int MAX_SIZE_STRING = 100;

int SizeOfStr(const char* str)
{
	int lengthOfStr = 0;
	while (*(str + lengthOfStr) != '\0')
	{
		++lengthOfStr;
	}
	return lengthOfStr;
}
int IndexOfElement(char str[], char element, int lengthOfStr)
{
	for (int i = 0; i < lengthOfStr; i++)
	{
		if (element == str[i])
			return i;

	}
	return -1;
}
void InsertionSort(int arr[], const int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		int j = i;
		while (j > 0)
		{
			if (arr[j] <= arr[j - 1])
			{
				int temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
			j--;
		}
	}
}
void ConcatStr(const char toAdd[], char destination[])
{
	int destinationLenght = SizeOfStr(destination);
	int i = 0;
	while (toAdd[i] != '\0')
	{
		destination[destinationLenght++] = toAdd[i++];

	}
	destination[destinationLenght] = '\0';
}
void CopyArray(const char copyFrom[], char destination[])
{
	int sizeOfCopyFrom = SizeOfStr(copyFrom);
	for (int i = 0; i < sizeOfCopyFrom; i++)
	{
		destination[i] = copyFrom[i];
	}
	destination[sizeOfCopyFrom] = '\0';
}
bool ContainsInArrayOfInteger(int arr[], int element, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		if (element == arr[i])
			return true;
	}
	return false;
}
bool ContainsInArrayOfStrings(char* checkedStrings[MAX_SIZE_STRING], int arrayStringsSize, char source[])
{
	int sizeOfSource = SizeOfStr(source);
	for (int i = 0; i < arrayStringsSize; i++)
	{
		int sizeOfChecked = SizeOfStr(checkedStrings[i]);
		if (sizeOfChecked != sizeOfSource)
		{
			continue;
		}
		bool flag = true;
		for (int j = 0; checkedStrings[i][j] != '\0'; j++)
		{
			if (source[j] != checkedStrings[i][j])
			{

				flag = false;
				break;
			}
		}
		if (flag)
			return flag;
		else
			continue;
	}
	return false;
}
bool HasOnlyLettersInside(const char* str, int lengthOfStr)
{
	for (int i = 0; i < lengthOfStr; i++)
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
			return false;

	}
	return true;
}
int CountOfDifferentStrings(const char str[])
{
	//we starting count from 1 because inputed string is also combination
	//ater k=0 scratched elements
	int lengthOfStr = SizeOfStr(str), countOfDifference = 1;


	//char *checkedStr[MAX_SIZE_STRING*MAX_SIZE_STRING] = {0};


	//we use heap allocated array of char array(with other words array of strings)
	//because we need to store already checked combination of strings with k scratched elements
	//example: aabv : abv one time after scratch first a, and also abv after scratch second a
	char** checkedStr = new char* [MAX_SIZE_STRING * MAX_SIZE_STRING];


	//k elements to scratch on iteration
	int k = 1, sizeOfCheckedStr = 0;


	while (k <= lengthOfStr - 1)
	{
		for (int i = 0; i < lengthOfStr; i++)
		{
			char* copyArray = (char*)malloc(MAX_SIZE_STRING * sizeof(char*));
			int arrIndexToScratch[MAX_SIZE_STRING] = {};
			int countScratch = 0, indexToScratch = i;
			int l = 0;
			//example if we have baab: and k=3
			//in first iteration we should scratch b with position 0
			//and k-1 following character so -> baa are scratched and possible combination
			//is b;
			while (countScratch < k)
			{
				//if we are baab at index str[3]=b and have to scratch k=2 following
				//we should scratch b at position 3 and after should jump again on the starting index
				//or abb (b) -> (a) bb (b) -> bb 
				if (indexToScratch == lengthOfStr) {
					indexToScratch = 0;
				}

				//we will store indexs of elements of str into arrIndexToScratch
				//if we have k=1 items to scratch will scratch each of following:
				//example: baab : (b with index 0) , (a with index 1) and so..
				//and we will have possible string after scratch like aab after scratch b at position 0
				arrIndexToScratch[countScratch] = indexToScratch;
				indexToScratch++;
				countScratch++;
			}
			//sort the indexes to scratch in ascending order for convenience
			InsertionSort(arrIndexToScratch, countScratch);
			if (copyArray) {
				for (int j = 0; j < lengthOfStr; j++)
				{
					//place elements with nonscratched indexes in copyArray
					if (!ContainsInArrayOfInteger(arrIndexToScratch, j, countScratch))
					{
						copyArray[l++] = str[j];
					}

				}
				copyArray[l] = '\0';
			}


			//checked if created string copyArray with non-scratched indexes is unique
			//because we need unique sequance
			//example: baab
			//we store baa,bab,aab,ba and so.. in checkedStr
			if (!ContainsInArrayOfStrings(checkedStr, sizeOfCheckedStr, copyArray))
			{
				checkedStr[sizeOfCheckedStr++] = copyArray;
				countOfDifference++;
			}
		}
		k++;
	}
	//delete open memory adresses to prevent memory leaks
	for (int w = 0; w < sizeOfCheckedStr; ++w)
		delete[] checkedStr[w];
	delete[] checkedStr;

	return countOfDifference;
}


int main()
{
	//we set str with size MAX_SIZE_STRING + 1 because we should check if user has inputed
	//more than MAX_SIZE_STRING chars, if he did we would have MAX_SIZE_STRING (one place reserved for null termination character)
	//length of str(SHOULD BE <MAX_SIZE_STRING) which is unallowable and we can handle this exception
	char str[MAX_SIZE_STRING + 1] = { 0 };
	cin.getline(str, MAX_SIZE_STRING + 1, '\n');
	int lengthOfStr = SizeOfStr(str);
	if (lengthOfStr >= MAX_SIZE_STRING || !HasOnlyLettersInside(str, lengthOfStr))
	{
		cout << "-1" << endl;
		return 0;
	}
	cout << CountOfDifferentStrings(str) << endl;

}