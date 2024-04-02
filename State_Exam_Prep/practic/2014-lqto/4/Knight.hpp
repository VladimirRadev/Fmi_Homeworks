#pragma once
#include "ChessPiece.hpp"

class Knight : public ChessPiece
{ 
    public:
        Knight();
        Knight(char d1,int d2);
        std::vector<ChessPosition> allowedMoves() override;
        bool captures(ChessPosition pos) override;
};