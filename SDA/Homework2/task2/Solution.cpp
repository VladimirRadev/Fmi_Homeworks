#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {

	unsigned int n = 0;
	cin >> n;
	vector<pair<string,unsigned int>>dates;
	string combine,firstPart,secondPart;
	getline(cin, combine, '\n');
	//22:44:05 11.04.2021
	for (long unsigned int i = 0; i < n; i++)
	{
		cin >> firstPart >> secondPart;
		string yyyyMmDd = secondPart.substr(6, 4) + secondPart.substr(3, 2) + secondPart.substr(0, 2);
		string hhMmSs = firstPart.substr(0, 2) + firstPart.substr(3, 2) + firstPart.substr(6, 2);
		combine = yyyyMmDd + hhMmSs;
		dates.push_back(pair<string,unsigned int>(combine,i+1));
		combine.clear();
		firstPart.clear();
		secondPart.clear();
	}

	sort(dates.begin(), dates.end());

	for (long unsigned int i = 0; i < n; i++)
	{
		cout << dates[i].second << endl;
	}
}
