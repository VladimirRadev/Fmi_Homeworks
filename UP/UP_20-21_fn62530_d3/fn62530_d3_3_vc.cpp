/**
*
* Solution to homework assignment 3
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
#include <cmath>

using namespace std;

bool AreEqualDoubles(double num1, double num2)
{
	return (fabs(num1 - num2) < pow(10, -9)) ? true : false;
}
double SumOfColums(double** matrix, int N)
{
	double magicSumOfColum = 0.0;
	for (int i = 0; i < N; i++)
	{
		double sumOfEachColum = 0.0;
		for (int j = 0; j < N; j++)
		{
			sumOfEachColum += matrix[j][i];
		}
		//set magicSumOfColum to first calulated sum of Colum then continue
		//because we are guaranteed that matrix has at least 2 colums
		if (i == 0)
		{
			magicSumOfColum = sumOfEachColum;
			continue;
		}
		//if sum of element in current colum isn't equal to magicSumOfColum
		//then it's unnecessary to check following
		if (!AreEqualDoubles(magicSumOfColum,sumOfEachColum))
		{
			return -1;
		}

	}
	return magicSumOfColum;
}
double SumOfDiagonals(double** matrix, int N)
{

	//main diagonal
	double sumOfMainDiagonal = 0.0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j)
			{
				sumOfMainDiagonal += matrix[i][j];
				break;
			}
			continue;
		}
	}
	//secondaryDiagonal
	double sumOfSecondaryDiagonal = 0.0;
	for (int i = 0; i < N; i++)
	{
		sumOfSecondaryDiagonal += matrix[i][N - i - 1];
	}
	if (!AreEqualDoubles(sumOfSecondaryDiagonal, sumOfMainDiagonal))
		return -1;
	else
		return sumOfSecondaryDiagonal;
	
}
double SumOfRows(double** matrix, int N)
{
	double magicSumOfRow = 0.0;
	for (int i = 0; i < N; i++)
	{
		double sumOfEachRow = 0.0;
		for (int j = 0; j < N; j++)
		{
			sumOfEachRow += matrix[i][j];
		}
		//set magicSumOfRow to first calulated sum of Row then continue
		//because we are guaranteed that matrix has at least 2 rows
		if (i == 0)
		{
			magicSumOfRow = sumOfEachRow;
			continue;
		}
		//if sum of element in current row isn't equal to magicSumOfRow
		//then it's unnecessary to check following
		if (!AreEqualDoubles(magicSumOfRow, sumOfEachRow))
		{
			return -1;
		}

	}
	return magicSumOfRow;
}
bool IsMagicSquare(double** matrix, int N)
{
	double sumOfRows = SumOfRows(matrix, N);
	double sumOfColums = SumOfColums(matrix, N);
	double sumOfDiagonals = SumOfDiagonals(matrix, N);
	//free taken memory prevent memory exceeds
	free(matrix);
	if (AreEqualDoubles(sumOfRows,-1.0) || AreEqualDoubles(sumOfColums, -1.0) || AreEqualDoubles(sumOfDiagonals, -1.0))
	{
		return false;
	}
	else if (AreEqualDoubles(sumOfRows, sumOfColums) && AreEqualDoubles(sumOfColums, sumOfDiagonals))
	{
		return true;
	}
	else
	{
		return false;
	}

}

int main()
{
	const int MAX_NATURAL = 1000;
	const double MAX_DOUBLE = 100.0;
	//we use malloc to allocate matrix of double with size 1000x1000
	//because exceeds stack memory
	double** matrix = (double**)malloc(MAX_NATURAL* sizeof(double*));
	//if allocation of matrix in memory was completed then start working with it
	if (matrix)
	{
		for (int i = 0; i < MAX_NATURAL; i++)
		{
			matrix[i] = (double*)malloc(MAX_NATURAL * sizeof(double));
		}

		int	N = 0;
		cin >> N;
		if (N <= 1 || N >= MAX_NATURAL) {
			cout << "-1" << endl;
			return 0;
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (matrix[i])
				{
					cin >> matrix[i][j];
					if (matrix[i][j] < 0 || matrix[i][j]>100)
					{
						cout << "-1" << endl;
						return 0;
					}
				}
			}

		}
		cout << boolalpha << IsMagicSquare(matrix, N) << endl;
	}

}