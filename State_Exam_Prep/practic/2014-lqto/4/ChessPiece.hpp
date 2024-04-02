#pragma once
#include "ChessPosition.hpp"
#include <vector>
class ChessPiece
{
protected:
    ChessPosition pos;
public:
    ChessPosition& getPosition();
    void setPosition(ChessPosition pos);

    virtual std::vector<ChessPosition> allowedMoves()=0;
    virtual bool captures(ChessPosition pos)=0;
};




