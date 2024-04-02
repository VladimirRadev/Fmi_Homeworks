#pragma once
#include "ChessPiece.hpp"
class Rook : public ChessPiece
{
    public:
        Rook(char d1,int d2);
        std::vector<ChessPosition> allowedMoves() override;
        bool captures(ChessPosition pos) override;
};