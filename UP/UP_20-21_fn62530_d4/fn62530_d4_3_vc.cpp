/**
*
* Solution to homework assignment 4
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
using namespace std;
struct Fraction 
{
	long long numerator;
	long long denominator;
};
long long GCD(long long a, long long b)
{
	if (a == 0)
	{
		return b;
	}
	else
	{
		return GCD(b % a, a);
	}
	
}
//lowest common denominator
long long LCD(long long denominator1, long long denominator2)
{
	long long numToDevide = 2,result=1;
	while (denominator1 != 1 || denominator2 != 1)
	{
		if (denominator1 % numToDevide == 0 && denominator2 % numToDevide==0)
		{
			result *= numToDevide;
			denominator1 /= numToDevide;
			denominator2 /= numToDevide;
			continue;
		}
		else if (denominator1 % numToDevide == 0 && denominator2 % numToDevide != 0)
		{
			result *= numToDevide;
			denominator1 /= numToDevide;
			continue;
		}
		else if (denominator1 % numToDevide != 0 && denominator2 % numToDevide == 0)
		{
			result *= numToDevide;
			denominator2 /= numToDevide;
			continue;
		}
		++numToDevide;
	}
	return result;
}
void simplificationOfFraction(Fraction* result)
{
	//the way we printing fraction with numerator zero
	if (result->numerator == 0)
	{
		result->denominator = 1;
		return;
	}
	else
	{
		long long numToDevide = 2;
		if (result->numerator <= result->denominator)
		{
			//while gcd(greatest common deviser) of the numerator and denominator is 1
			//try to devide the numerator and denominator with common deviser
			// for example (4 6) try divide 4 and 6 with 2 -> true 4,6 is dividable by 2 so 
			// (4 6)-> 2 3  (gcd of 2 and 3 is 1 ) because 2 and 3 are simple by each other
			//so 2 3 is the simplifying of result fraction
			while (GCD(result->numerator, result->denominator) != 1)
			{
				if (result->numerator % numToDevide == 0 && result->denominator % numToDevide == 0)
				{
					result->numerator /= numToDevide;
					result->denominator /= numToDevide;
				}
				else
				{
					numToDevide++;
				}
			}
			return;
		}
		else
		{
			//same story but changed position of denominator and numerator because gcd working with
			//arguments a,b where a<=b;
			while (GCD(result->denominator, result->numerator) != 1)
			{
				if (result->numerator % numToDevide == 0 && result->denominator % numToDevide == 0)
				{
					result->numerator /= numToDevide;
					result->denominator /= numToDevide;
				}
				else
				{
					numToDevide++;
				}
			}
			return;

		}
	}
}
void printArray(long long* arr)
{
	cout << arr[0] << " " << arr[1]<<endl;
	delete[]arr;
}
long long* CalculateOperation(long long numerator1,long long denominator1,long long numerator2,long long denominator2, char* operation)
{
	long long* result = new long long[2];
	Fraction firstFraction = { 0,0 };
	firstFraction.numerator = numerator1;
	firstFraction.denominator = denominator1;
	Fraction secondFraction = { 0,0 };
	secondFraction.numerator = numerator2;
	secondFraction.denominator = denominator2;
	if (operation[0] == '+') 
	{
		//common denominator we calculating with LCD (lowest common deviser ) function
		long long commonDenominator = LCD(firstFraction.denominator, secondFraction.denominator);
		long long numerator1ToAdd = firstFraction.numerator * (commonDenominator / (firstFraction.denominator));
		long long numerator2ToAdd = secondFraction.numerator * (commonDenominator / (secondFraction.denominator));
	    //we will store the result fraction in fractionresult
		Fraction fractionResult = { 0,0 };
		fractionResult.numerator = numerator1ToAdd + numerator2ToAdd;
		fractionResult.denominator = commonDenominator;

	    //if we have for example: (-2 3) + (1 3) = -1 3 and simplificationOfFraction function working only
		//with positives number so we will get the absolute value of numerator and then after simplify function
		//we will concat this minus in front of the numerator 
		if (fractionResult.numerator < 0)
		{
			fractionResult.numerator = abs(fractionResult.numerator);
			simplificationOfFraction(&fractionResult);
			result[0] = -(fractionResult.numerator);
			result[1] = fractionResult.denominator;
		}
		else {
			simplificationOfFraction(&fractionResult);
			result[0] = fractionResult.numerator;
			result[1] = fractionResult.denominator;
		}
		return result;
	}

	else if (operation[0] == '-')
	{
		long long commonDenominator = LCD(firstFraction.denominator, secondFraction.denominator);
		long long numerator1ToAdd = firstFraction.numerator * (commonDenominator / (firstFraction.denominator));
		long long numerator2ToAdd = secondFraction.numerator * (commonDenominator / (secondFraction.denominator));
		Fraction fractionResult = { 0,0 };
		fractionResult.numerator = numerator1ToAdd - numerator2ToAdd;
		fractionResult.denominator = commonDenominator;

		//if we have for example: (1 3) - (2 3) = -1 3 and simplificationOfFraction function working only
	    //with positives number so we will get the absolute value of numerator and then after simplify function
	    //we will concat this minus in front of the numerator 
		if (fractionResult.numerator < 0)
		{
			fractionResult.numerator = abs(fractionResult.numerator);
			simplificationOfFraction(&fractionResult);
			result[0] = -(fractionResult.numerator);
			result[1] = fractionResult.denominator;
		}
		else {
			simplificationOfFraction(&fractionResult);
			result[0] = fractionResult.numerator;
			result[1] = fractionResult.denominator;
		}
		return result;
	}
	else if (operation[0] == '*')
	{
		long long numeratorsMultiplication = firstFraction.numerator * secondFraction.numerator;
		long long denominatorsMultiplication = firstFraction.denominator * secondFraction.denominator;
		Fraction fractionResult = { 0,0 };
		fractionResult.numerator = numeratorsMultiplication;
		fractionResult.denominator = denominatorsMultiplication;
	    
		//if one of the multiplyers is with negative numerator the result of multiplication will be
		//also a negative number but simplificationOfFraction working with positive numbers only
		//so we solve this problem as the same way as when operator is '+' or '-'
		if (fractionResult.numerator < 0)
		{
			fractionResult.numerator = abs(fractionResult.numerator);
			simplificationOfFraction(&fractionResult);
			result[0] = -fractionResult.numerator;
			result[1] = fractionResult.denominator;
		}
		else {
			simplificationOfFraction(&fractionResult);
			result[0] = fractionResult.numerator;
			result[1] = fractionResult.denominator;
		}
		return result;
	}
	else if (operation[0] == '/')
	{
		//if we have (1 8) / (1 3) -> the way we calculate the result is (1*3 1*8) firstFracNumerator*secFracDeterminator
		//and firstFracDenominator*secondFracNumerator
		long long numeratorsMultiplication = firstFraction.numerator * secondFraction.denominator;
		long long denominatorsMultiplication = firstFraction.denominator * secondFraction.numerator;
		Fraction fractionResult = { 0,0 };
		fractionResult.numerator = numeratorsMultiplication;
		fractionResult.denominator = denominatorsMultiplication;
		//if we have (-1 8 )/(-2 8)= the result also will be positive so we get the absolute value of
		//fracResult calculated numerator and denominator
		if (fractionResult.numerator < 0 && fractionResult.denominator<0)
		{
			fractionResult.numerator = abs(fractionResult.numerator);
			fractionResult.denominator = abs(fractionResult.denominator);
			simplificationOfFraction(&fractionResult);
			result[0] = fractionResult.numerator;
			result[1] = fractionResult.denominator;
		}
		//if we have (1 8) / (-2 8) or (-1 8)/(2 8) the result will be negative so we also get the absolute value
		//of fracResult numerator and denominator but after simplifaiying concat a minus in front of fracResult numerator
		else if (fractionResult.numerator < 0 || fractionResult.denominator < 0)
		{
			fractionResult.numerator = abs(fractionResult.numerator);
			fractionResult.denominator = abs(fractionResult.denominator);
			simplificationOfFraction(&fractionResult);
			result[0] = -fractionResult.numerator;
			result[1] = fractionResult.denominator;
		}
		else 
		{
			simplificationOfFraction(&fractionResult);
			result[0] = fractionResult.numerator;
			result[1] = fractionResult.denominator;
		}
		return result;
	
	}
}
int main()
{
	const int MAXIMUM_VALUE_OF_NUMBER = (int)pow(10, 8);
	const int MINIMUM_VALUE_OF_NUMBER = -(int)pow(10, 8);
	long long numerator1 = 0, denominator1 = 0, numerator2 = 0, denominator2 = 0;
	char operation[2] = { 0 };
	cin >> numerator1>>denominator1;
	if (numerator1<MINIMUM_VALUE_OF_NUMBER || numerator1>MAXIMUM_VALUE_OF_NUMBER)
	{
		cout << "-1" << endl;
		return 0;
	}
	//denominator can't be zero or negative by lector's instructions
	if (denominator1<=0 || denominator1>MAXIMUM_VALUE_OF_NUMBER)
	{
		cout << "-1" << endl;
		return 0;
	}
	cin >> operation;
	if (operation[0] != '+' && operation[0] != '-' && operation[0] != '*' && operation[0] != '/')
	{
		cout << "-1" << endl;
		return 0;
	}
	cin >> numerator2;
	//if we deviding a fraction by fraction the second fraction's denominator and numerator always must be
	//a value different from zero
	if (operation[0] == '/' && numerator2 == 0)
	{
		cout << "-1" << endl;
		return 0;
	}
	if (numerator2<MINIMUM_VALUE_OF_NUMBER || numerator2>MAXIMUM_VALUE_OF_NUMBER)
	{
		cout << "-1" << endl;
		return 0;
	}
	cin >> denominator2;
	//denominator can't be zero or negative by lector's instructions
	if (denominator2<=0|| denominator2>MAXIMUM_VALUE_OF_NUMBER)
	{
		cout << "-1" << endl;
		return 0;
	}
	printArray(CalculateOperation(numerator1,denominator1,numerator2,denominator2, operation));
	return 0;
}
