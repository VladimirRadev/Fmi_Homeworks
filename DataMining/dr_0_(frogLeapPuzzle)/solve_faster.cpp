#include <bits/stdc++.h>
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <stack>
#include <utility>
// n = readInput();
// size = (n * 2) + 1;
// board = new board[size];
// function dfs(board, zeroState) {
// if isGoalState(board, zeroState)
// return TRUE;
// for move in moves(board, zeroState) {
// if dfs(move.board, move.zeroState) {
// print(move.board);
// return TRUE;
// }
// }
// return FALSE;
// }

std::stack<char*> printRes;
int n = 0, size = 0;

//returns vector of moves and index of the empty rock within them
std::vector<std::pair<char *,int>> moves(const char *board,const int& parentEmptyRockIndex)
{
    std::vector<std::pair<char *,int>> res;
    for (int i = parentEmptyRockIndex - 2; i <= parentEmptyRockIndex + 2; i++)
    {
        if(i < 0 || i >= size) {
            continue;
        }
        //L on the left of the emptyrock
        if(board[i] == '>' && parentEmptyRockIndex > i) {
            std::pair<char *,int> move;
            move.first=new char[size+1];
            for (size_t j = 0; j < size; j++)
            {
                move.first[j]=board[j];
            }
            move.first[i]='_';
            move.first[parentEmptyRockIndex]='>';
            move.second=i;            
            move.first[size]='\0';
            res.push_back(move);
        }

         //R on the right of the emptyrock
        if(board[i] == '<' && parentEmptyRockIndex < i) {
            std::pair<char *,int> move;
            move.first=new char[size+1];
            for (size_t j = 0; j < size; j++)
            {
                move.first[j]=board[j];
            }
            move.first[i]='_';
            move.first[parentEmptyRockIndex]='<';
            move.second=i;            
            move.first[size]='\0';
            res.push_back(move);
        }
    }
    
    return res;
}
bool isGoalState(const char *board, const int &emptyRockIndex)
{
    if (emptyRockIndex != size / 2)
    {
        return false;
    }
    else
    {
        
        for (size_t i = 0; i < size / 2; i++)
        {
            if (board[i] != '<')
            {
                return false;
            }
        }
        return true;
    }
}
bool dfs(char *board, int emptyRockIndex)
{
    if (isGoalState(board, emptyRockIndex))
    {
        return true;
    }
    std::vector<std::pair<char *,int>> moves_ = moves(board,emptyRockIndex);
    for (const std::pair<char*, int>& move : moves_)
    {
        if (dfs(move.first, move.second))
        {
            printRes.push(move.first);
            return true;
        }
    }
    return false;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    time_t start, end; 


    std::cin >> n;
    size = n * 2 + 1;
    // std::cout<<"The value of 'size' is : " << size <<std::endl;
    std::vector<char *> res;
    char *board = new char[size + 1];
    for (size_t i = 0; i < size / 2; i++)
    {
        board[i] = '>';
    }
    board[size / 2] = '_';
    for (size_t i = size / 2 + 1; i < size; i++)
    {
        board[i] = '<';
    }
    board[size + 1] = '\0';
    std::cout<<board<<"\n";

    time(&start); 
    dfs(board,size/2);
    // print stack
    // while (!printRes.empty())
    // {
    //     std::cout<<printRes.top()<<"\n";
    //     printRes.pop();
    // }
    time(&end);

    double time_taken = double(end - start); 
    std::cout << "Time taken by program is : " << std::fixed << std::setprecision(2) << time_taken << " sec " << std::endl;
    return 0;
    
}