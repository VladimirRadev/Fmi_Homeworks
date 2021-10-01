/**
*
* Solution to homework assignment 3
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
#include <cmath>
#include <fstream>
using namespace std;

int SizeOfStr(const char* str)
{
	int index = 0;
	while (*(str + index) != '\0')
	{
		index++;
	}
	return index;

}
bool HasOnlyLettersInside(const char* str, int lengthOfStr)
{
	for (int i = 0; i < lengthOfStr; i++)
	{
		if (!(str[i] >= 'A' && str[i] <= 'z'))
			return false;

	}
	return true;
}
void InsertionSort(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		int j = i;
		while (j > 0)
		{
			if (str[j] <= str[j - 1])
			{
				int temp = str[j - 1];
				str[j - 1] = str[j];
				str[j] = (char)temp;
			}
			j--;
		}

	}
}

int main()
{
	const int MAX_STRING_SIZE = 150;
	char str[MAX_STRING_SIZE + 2] = { 0 };
	ifstream file;
	file.open("massage.txt", ios::in);
	if (!file)
	{
		cout << "-2" << endl;
		return 0;
	}
	//we allocate enough space in heap because there is no limit of massage.txt
	//mentioned in problem description
	char *bingoWord = new char[MAX_STRING_SIZE*MAX_STRING_SIZE];
	int bingoWordSize = 0;
	while (file.getline(str, MAX_STRING_SIZE+2, '\n'))
	{
		int lineLenght = SizeOfStr(str);
		if (lineLenght == 0)
		{
			continue;
		}
		if (lineLenght > MAX_STRING_SIZE || !HasOnlyLettersInside(str, lineLenght))
		{
			cout << "-1" << endl;
			return 0;
		}
		//sort element in ascending order by ASCII codes
		InsertionSort(str);
		int counter = 0,asciOfCharToAdd=0;
		do
		{
			if (counter + 1 >= lineLenght)
			{
				//in case sush as: XYZ -> then spy code is 'a' because after upper Letters following lower
				if (str[counter]=='Z')
				{
					asciOfCharToAdd = (int)('a');
					break;
				}
				//in case as: xyz-> '.' is only available spy code 
				if (str[counter] == 'z')
				{
					asciOfCharToAdd = (int)'.';
					break;
				}
				//else give me asci code of str[counter]+1
				//example: abc-> spycode='c'+ 1 ='d';
				asciOfCharToAdd = (int)str[counter] + 1;
				break;
			}
			//in case as XYabvz -> we have a "jump" from upper to lower letter 
			if ((str[counter + 1] - str[counter]) >= ('a' - 'Z'))
			{
				//we are using XYabvz as example
				//if Y!='Z' so set asciOfCharToAdd= 'Y'+ 1;
				if (str[counter] != 'Z')
				{
					asciOfCharToAdd = (int)str[counter] + 1;
					break;
				}

				//we are using XYZbvz as example
				//if b!='a' so set asciOfCharToAdd= 'a';
				if (str[counter + 1] != 'a')
				{
					asciOfCharToAdd = (int)'a';
					break;
				}

				//in every other case 
				//we are using XYZabvz as example
				//set asciOfCharToAdd to (int)str[counter+1] ('a' in this example) and 
				//continue with next iteration
				asciOfCharToAdd = (int)str[counter+1];
				counter++;
				continue;
			}
			//in case as: acde || aaaaacdddee ( not unique symbols)
			//we starting from a and check the if statemant which in this case is true
			//enter in it and set asciOfCharToAdd to 'a'+ 1 =(int)'b'
			if ((str[counter] + 1) != str[counter + 1] && str[counter]!=str[counter+1])
			{
				asciOfCharToAdd = (int)str[counter] + 1;
				break;
			}
			asciOfCharToAdd = (int)str[counter + 1] + 1;
			counter++;
 		} while (str[counter] + 1 == str[counter + 1] || (str[counter] + 1 >'Z') || str[counter]==str[counter+1]);
		bingoWord[bingoWordSize++] = asciOfCharToAdd;
	}
	bingoWord[bingoWordSize] = '\0';
	cout << bingoWord << endl;
	delete[]bingoWord;
	file.close();
}