#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;


int main() {
    int n = 0, k = 0;
    int maxPositiveNumber = INT_MIN;
    cin >> n;
    int* numContainer = new int[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> k;
        if (k > maxPositiveNumber)
        {
            maxPositiveNumber = k;
        }
        numContainer[i] = k;
    }
    unsigned int positiveNumContainerLength = maxPositiveNumber + 1;
    bool* positiveNumContainer = new bool[positiveNumContainerLength] {};
    for (int l = 0; l < n; ++l)
    {
        if (numContainer[l] >= 1 && !positiveNumContainer[numContainer[l]])
        {
            positiveNumContainer[numContainer[l]] = true;
        }
    }
    unsigned int result = 0;
    for (unsigned int z = 1; z < positiveNumContainerLength; ++z)
    {
        if (positiveNumContainer[z] == false)
        {
            result = z;
            break;
        }
    }
    if (result == 0)
    {
        result = positiveNumContainerLength;
    }
    cout << result << endl;

    delete[]numContainer;
    delete[]positiveNumContainer;



}