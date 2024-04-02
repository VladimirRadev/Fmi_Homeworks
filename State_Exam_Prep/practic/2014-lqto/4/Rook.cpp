#include "Rook.hpp"
Rook::Rook(char d1,int d2)
{
    this->pos.d1=d1;
    this->pos.d2=d2;
}
std::vector<ChessPosition> Rook::allowedMoves() 
{
    
    std::vector<ChessPosition> res;
    for(char k = 'A';k<='H';k++)
    {
        if(this->pos.d1 == k)
        {
            continue;
        }
        res.push_back(ChessPosition(k,this->pos.d2));
    }
    for (int i = 1; i <= 8; i++)
    {
        if(this->pos.d2==i)
        {
            continue;
        }
        res.push_back(ChessPosition(this->pos.d1,i));
    }
    return res;
}
bool Rook::captures(ChessPosition pos) 
{
    if(this->pos==pos)
    {
        return true;
    }
    return (this->pos.d1==pos.getD1() || this->pos.d2==pos.getD2());
}