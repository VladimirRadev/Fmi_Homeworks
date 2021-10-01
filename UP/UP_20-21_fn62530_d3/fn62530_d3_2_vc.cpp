/**
*
* Solution to homework assignment 3
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

//we use MAX as global variable because we using it
//in more than one function and would be not practical if every
//function takes it as argument in its declaration
const short MAX = 1000;

int SizeOfStr(char* str)
{
	int offset = 0;
	int lengthOfStr = 0;
	while (*(str + offset) != '\0')
	{
		++lengthOfStr;
		++offset;
	}
	return lengthOfStr;
}
int IndexOfElement(char str[], char element,int lengthOfStr)
{
	for (int i = 0; i < lengthOfStr; i++)
	{
		if (element == str[i])
			return i;

	}
	return -1;
}
void CopyArray(char copyFrom[],char destination[])
{
	int sizeOfCopyFrom = SizeOfStr(copyFrom);
	for (int i = 0; i < sizeOfCopyFrom; i++)
	{
		destination[i] = copyFrom[i];
	}
	destination[sizeOfCopyFrom] = '\0';
}
bool ContainsInArray(char str[], int arraySize, char check)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (str[i] == check)
		{
			return true;
		}

	}
	return false;
}

bool PossibleConcatination(char str1[], char str2[], char check[])
{
	int lengthOfStr1 = SizeOfStr(str1), lengthOfStr2 = SizeOfStr(str2), 
		lengthOfCheck = SizeOfStr(check);
	for (int i = 0; i < lengthOfCheck; i++)
	{
		//we will search for each char of check arr in one of str1 or str2
		//if we find such char then will "delete" this char from str1 or str2
		//and after algorithum if str1 and str2 sizes are zero it means
		//check is created by concatination of str1 and str2
		if (ContainsInArray(str1,lengthOfStr1,check[i]))
		{
			char copyStr1[MAX] = {};
			int copyStr1Size=0;
			if (lengthOfStr1 == 1)
			{
				lengthOfStr1--;
				str1[0]='\0';
				continue;
			}
			else
			{
				for (int k = 0; k < lengthOfStr1; k++)
				{
					//copy all elements of str1 to copyStr1 excluding element we want to delete
					//example: aa bb aabb. We are at pos 0 in aabb str. We see that aa contains a
					//so delete first a from aa -> a bb aabb
					if (k == IndexOfElement(str1, check[i], lengthOfStr1))
					{
						continue;
					}

					copyStr1[copyStr1Size++] = str1[k];

				}
				CopyArray(copyStr1, str1);
				lengthOfStr1--;
			}
		}
		else if (ContainsInArray(str2, lengthOfStr2, check[i]))
		{
			char copyStr2[MAX] = {};
			int copyStr2Size = 0;
			if (lengthOfStr2 == 1)
			{
				lengthOfStr2--;
				str2[0] = '\0';
				continue;
			}
			else
			{
				for (int k = 0; k < lengthOfStr2; k++)
				{
					//copy all elements of str1 to copyStr2 excluding element we want to delete
					//example: aa bb aabb. We are at pos 2 in aabb str. We see that bb contains b
					//so delete first b from bb -> aa b aabb
					if (k == IndexOfElement(str2, check[i], lengthOfStr2))
					{
						continue;
					}
					copyStr2[copyStr2Size++] = str2[k];

				}
				CopyArray(copyStr2, str2);
				lengthOfStr2--;
			}
		}
		//if current check[i] element is not in str1 or str 2 then return false
		//example: aa bb aabc -> check[3]=c is not find  in str1 or str2 then aabc 
		//is not concat of str1 and str2
		else
		{
			return false;
		}
	}
	//if after all iteration lengthOfStr1 and LengthofStr2 are equal it means 
	//each element of check was found in str1 or str2.then it's possible concatination
	if (lengthOfStr1 == 0 && lengthOfStr2 == 0)
	{
		return true;

	}
	else
	{
		return false;
	}
}
bool ValidateData(char str1[], char str2[], char check[], int lengthOfStr1,
	int lengthOfStr2, int lengthOfCheck,const short MAX_STRING_CHARECTERS)
{
	if (lengthOfStr1 > MAX_STRING_CHARECTERS || lengthOfStr2 > MAX_STRING_CHARECTERS || lengthOfCheck > MAX_STRING_CHARECTERS)
	{
		return false;
	}
	for (int i = 0; i < lengthOfStr1; i++)
	{
		if (str1[i] < 'a' || str1[i]>'z')
		{
			return false;
		}

	}
	for (int i = 0; i < lengthOfStr2; i++)
	{
		if (str2[i] < 'a' || str2[i]>'z')
		{
			return false;
		}

	}
	for (int i = 0; i < lengthOfCheck; i++)
	{
		if (check[i] < 'a' || check[i]>'z')
		{
			return false;
		}

	}

	return true;
}
int main()
{
	const short MAX_STRING_CHARECTERS = 150;
	char str1[MAX],str2[MAX],check[MAX];
	int lengthOfStr1 = -1, lengthOfStr2 = -1, lengthOfCheck = -1;
	cin >> str1 >> str2 >> check;
	lengthOfStr1 = SizeOfStr(str1);
	lengthOfStr2 = SizeOfStr(str2);
	lengthOfCheck = SizeOfStr(check);
	if (!ValidateData(str1, str2, check, lengthOfStr1, lengthOfStr2, lengthOfCheck,MAX_STRING_CHARECTERS))
	{
		cout << "-1" << endl;
		return 0;
	}
	cout << PossibleConcatination(str1,str2,check) << endl;

}