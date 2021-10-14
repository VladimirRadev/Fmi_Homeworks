#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;


int main() {

    string variants;
    char remainingVariant = '\0';

    cin >> variants >> remainingVariant;
    int* distanceToRemainingVariant = new int[variants.length()];
    for (long unsigned int i = 0; i < variants.length(); ++i)
    {
        if (variants[i] == remainingVariant)
        {
            distanceToRemainingVariant[i] = 0;
            continue;
        }

        int distanceToBottom = -1;


        for (int j = i; j >= 0; --j)
        {
            if (variants[j] == remainingVariant)
            {
                distanceToBottom = i - j;
                break;
            }

        }
        int distanceToTop = -1;

        for (long unsigned int k = i; k < variants.length(); ++k)
        {
            if (variants[k] == remainingVariant)
            {
                distanceToTop = k - i;
                break;
            }


        }
        if (distanceToBottom == -1 && distanceToTop == -1)
        {
            distanceToRemainingVariant[i] = (variants.length() - 1) - i;
        }
        else if (distanceToBottom == -1 && distanceToTop != -1)
        {
            distanceToRemainingVariant[i] = distanceToTop;
        }
        else if (distanceToBottom != -1 && distanceToTop == -1)
        {
            distanceToRemainingVariant[i] = distanceToBottom;
        }
        else
        {
            distanceToRemainingVariant[i] = min(distanceToBottom, distanceToTop);
        }
    }
    for (long unsigned int i = 0; i < variants.length(); ++i)
    {
        cout << distanceToRemainingVariant[i] << ' ';
    }
    cout << endl;

}