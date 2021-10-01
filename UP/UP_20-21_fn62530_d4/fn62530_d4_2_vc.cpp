/**
*
* Solution to homework assignment 4
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
bool possibleMovementOfKnight(int N, int M, int p, int q, int p1, int q1, int k, bool& trigger)
{
	//if the trigger is set to true it means that is possible knight to be in position
	//(p1,q1) after max k movements. So when the trigger is true return true in every recursion's node
	if (trigger)
	{
		return trigger;
	}
	//if (p,q)==(p1,q1) it means somewhere in recursion' tree node has a possible knight move
	//and set the trigger to true
	if (p == p1 && q == q1 && k>=0)
	{
		trigger = true;
	}
	// if we trying to go outside the board borders or we are out of moves(k) 
	if (p < 0 || q<0 || p>=N || q>=M || k < 0)
	{
		return trigger;
	}
	//here we trying every possible move of knight in one traditional chess game (they are 8)
	//we are going in depth into recursion tree' nodes and check whether a knight is on position (p1,q1)
	//we are making this till the next move is outside the board borders or we are out of moves. When this happens
	//we make a step back and tries a one of the next (8-1) paths on the board and so... till we checked
	//all possible moves of knight with given k moves
	possibleMovementOfKnight(N, M, p + 1, q + 2, p1, q1, k - 1, trigger);
	possibleMovementOfKnight(N, M,p - 2, q - 1, p1 ,q1, k - 1, trigger);
	possibleMovementOfKnight(N, M, p - 1, q - 2,p1,q1, k - 1, trigger);
	possibleMovementOfKnight(N, M, p + 1, q - 2,p1,q1, k - 1, trigger);
	possibleMovementOfKnight(N, M, p + 2, q - 1, p1, q1, k - 1, trigger);
	possibleMovementOfKnight(N, M, p + 2, q + 1, p1, q1, k - 1, trigger);
	possibleMovementOfKnight(N, M, p - 1, q + 2, p1, q1, k - 1, trigger);
	possibleMovementOfKnight(N, M, p - 2, q + 1, p1, q1, k - 1, trigger);
	return trigger;
}
int main()
{
	int N = 0, M = 0, p = 0, q = 0, p1 = 0, q1 = 0, k = 0;
	bool trigger = false;
	const int MIN_POSSIBLE_VALUE_OF_N_M = 3;
	const int MAX_POSSIBLE_VALUE_EXCLUDING_K = 200;
	const int MIN_POSSIBLE_VALUE_OF_K = 0;
	const int MAX_POSSIBLE_VALUE_OF_K = 30;
	cin >> N >> M;
	if (N<=MIN_POSSIBLE_VALUE_OF_N_M || N>MAX_POSSIBLE_VALUE_EXCLUDING_K)
	{
		cout << "-1" << endl;
		return 0;
	}
	if (M<=MIN_POSSIBLE_VALUE_OF_N_M || M>MAX_POSSIBLE_VALUE_EXCLUDING_K)
	{
		cout << "-1" << endl;
		return 0;
	}
	cin >> p >> q;
	if ((p<MIN_POSSIBLE_VALUE_OF_K || p>MAX_POSSIBLE_VALUE_EXCLUDING_K) || (p>=N))
	{
		cout << "-1" << endl;
		return 0;
	}
	if ((q<MIN_POSSIBLE_VALUE_OF_K || q>MAX_POSSIBLE_VALUE_EXCLUDING_K) || (q >= M))
	{
		cout << "-1" << endl;
		return 0;
	}
	cin >> p1 >> q1;
	if ((p1<MIN_POSSIBLE_VALUE_OF_K || p1>MAX_POSSIBLE_VALUE_EXCLUDING_K) || (p1 >= N))
	{
		cout << "-1" << endl;
		return 0;
	}
	if ((q1<MIN_POSSIBLE_VALUE_OF_K || q1>MAX_POSSIBLE_VALUE_EXCLUDING_K) || (q1 >= M))
	{
		cout << "-1" << endl;
		return 0;
	}
	cin >> k;
	if (k<=MIN_POSSIBLE_VALUE_OF_K || k>MAX_POSSIBLE_VALUE_OF_K)
	{
		cout << "-1" << endl;
		return 0;
	}
	bool result=possibleMovementOfKnight(N, M, p, q, p1, q1, k, trigger);
	if (result)
	{
		cout << "True" << endl;
		return 0;
	}
	else
	{
		cout << "False" << endl;
		return 0;
	}

}