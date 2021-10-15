#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void merge(int* array, int l, int m, int r) {
    int i, j, k, nl, nr;
    nl = m - l + 1; 
    nr = r - m;
    int* larr = new int[nl];
    int* rarr = new int[nr];
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0; j = 0; k = l;
    while (i < nl && j < nr) {
        if (larr[i] <= rarr[j]) {
            array[k] = larr[i];
            i++;
        }
        else {
            array[k] = rarr[j];
            j++;
        }
        k++;
    }
    while (i < nl) {       
        array[k] = larr[i];
        i++; k++;
    }
    while (j < nr) {     
        array[k] = rarr[j];
        j++; k++;
    }
    delete[]larr;
    delete[]rarr;
}
void mergeSort(int* array, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}
int main() {

	unsigned int n = 0, k = 0;
	cin >> n;

	int* presentsPrice = new int[n];
	int input = 0;
	for (long unsigned int i = 0; i < n; i++)
	{
		cin >> input;
		presentsPrice[i] = input;
	}
    mergeSort(presentsPrice, 0, n - 1);
	std::cin >> k;
	long long sum = 0;
	for (long unsigned int i = 0; i < k; i++)
	{
		sum += presentsPrice[i];
	}
	cout << sum << endl;

	delete[]presentsPrice;
}
