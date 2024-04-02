#include "Knight.hpp"
#include <cmath>
Knight::Knight(){}
Knight::Knight(char d1,int d2)
{
    this->pos.d1=d1;
    this->pos.d2=d2;
}
std::vector<ChessPosition> Knight::allowedMoves()
{
    std::vector<ChessPosition> res;
    for (char k = 'A'; k <= 'H'; k++)
    {
        for (int i = 1; i <= 8; i++)
        {
            if((abs(this->pos.d1 - k) == 2 && abs(this->pos.d2 - i ) == 1) 
                || ((abs(this->pos.d1 - k) == 1 && abs(this->pos.d2 - i ) == 2)))
            {
                res.push_back(ChessPosition(k,i));
            }
        }
        
    }
    return res;
}
bool Knight::captures(ChessPosition pos) 
{
    if(this->pos==pos)
    {
        return true;
    }
    return (abs(this->pos.d1 - pos.d1) == 2 && abs(this->pos.d2 - pos.d2 ) == 1) 
                || ((abs(this->pos.d1 - pos.d1) == 1 && abs(this->pos.d2 - pos.d2 ) == 2));
}