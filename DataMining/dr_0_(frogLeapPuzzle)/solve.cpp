#include <iostream>
#include <vector>
#include <stack>
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

int findEmpty(const char* board) {
    for (size_t i = 0; i < size; i++)
    {
        if(board[i] == '_') {
            return i;
        }
    }
    return -1;
}
std::vector<char *> moves(const char *board)
{
    std::vector<char *> res;
    for (size_t i = 0; i < size; i++)
    {
        if (board[i] == '>')
        {
            // L double jumps
            if (i + 2 < size && board[i + 2] == '_')
            {
                char *move = new char[size + 1];
                for (size_t i = 0; i < size; i++)
                {
                    move[i] = board[i];
                }
                move[i] = '_';
                move[i + 2] = '>';
                move[size] = '\0';
                res.push_back(move);
            }

            // L jumps
            if (i + 1 < size && board[i + 1] == '_')
            {
                char *move = new char[size + 1];
                for (size_t i = 0; i < size; i++)
                {
                    move[i] = board[i];
                }
                move[i] = '_';
                move[i + 1] = '>';
                move[size] = '\0';
                res.push_back(move);
            }
        }
        else if (board[i] == '<')
        {
            // R jumps
            if (i - 1 >= 0 && board[i - 1] == '_')
            {
                char *move = new char[size + 1];
                for (size_t i = 0; i < size; i++)
                {
                    move[i] = board[i];
                }
                move[i] = '_';
                move[i - 1] = '<';
                move[size] = '\0';
                res.push_back(move);
            }

            // R double jumps
            if (i - 2 >= 0 && board[i - 2] == '_')
            {
                char *move = new char[size + 1];
                for (size_t i = 0; i < size; i++)
                {
                    move[i] = board[i];
                }
                move[i] = '_';
                move[i - 2] = '<';
                move[size] = '\0';
                res.push_back(move);
            }
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
        bool state = true;
        for (size_t i = 0; i < size / 2; i++)
        {
            if (board[i] != '<')
            {
                state = false;
                break;
            }
        }
        return true ? state : false;
    }
}
bool dfs(char *board, int emptyRockIndex)
{
    if (isGoalState(board, emptyRockIndex))
    {
        return true;
    }

    for (char *move : moves(board))
    {
        int emptyRockIndexNow = findEmpty(move);
        if (dfs(move, emptyRockIndexNow))
        {
            printRes.push(move);
            return true;
        }
    }
    return false;
}
int main()
{

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
    std::cout<<board<<std::endl;
    dfs(board,size/2);
    // print stack
    while (!printRes.empty())
    {
        std::cout<<printRes.top()<<std::endl;
        printRes.pop();
    }
    
}