#include "ChessPiece.hpp"
ChessPosition& ChessPiece::getPosition()
{
    return pos;
}
void ChessPiece::setPosition(ChessPosition pos)
{
    this->pos=pos;
}