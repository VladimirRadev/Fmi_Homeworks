#include "ChessPosition.hpp"
ChessPosition::ChessPosition(){}
ChessPosition::ChessPosition(char d1,int d2):d1(d1),d2(d2){}
char ChessPosition::getD1()const
{
    return this->d1;
}
int ChessPosition::getD2()const
{
    return this->d2;
}
std::string ChessPosition::stringify()const
{
        std::string res;
        res+=d1;
        res+=std::to_string(d2);
        return res;
}
bool ChessPosition::operator==(const ChessPosition&other)const
{
    return (this->d1==other.getD1() && this->d2==other.getD2());
}