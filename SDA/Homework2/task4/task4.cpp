#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


double calcEfficiency(int ti, int di)
{
    return (double)(pow(di, 2) / ti);
}
int main() {

    unsigned int n = 0;
    cin >> n;
    //pair<index,pair<di,ti>>
    vector<pair<int, pair<int, int>>>efficiencies;
    int di = 0, ti = 0;
    for (long unsigned int i = 0; i < n; i++)
    {
        cin >> di >> ti;
        efficiencies.push_back(pair<int, pair<int, int>>(i + 1, pair<int, int>(di, ti)));
    }
    sort(efficiencies.begin(), efficiencies.end(), [](auto a, auto b) {

        if (calcEfficiency(a.second.second, a.second.first) > calcEfficiency(b.second.second, b.second.first))
        {
            return true;
        }
        else if (calcEfficiency(a.second.second, a.second.first) < calcEfficiency(b.second.second, b.second.first))
        {
            return false;
        }
        else
        {
            if (a.second.first > b.second.first)
            {
                return true;
            }
            else
            {
                return false;
            }
        }


    });

    for (long unsigned int i = 0; i < n; i++)
    {
        cout << efficiencies[i].first << ' ';
    }
    cout << endl;

    return 0;
}

