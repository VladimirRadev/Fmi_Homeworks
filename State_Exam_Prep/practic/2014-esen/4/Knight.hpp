#pragma once
#include "GamePlayer.hpp"
class Knight : public GamePlayer
{
    public:
        Knight(const int& x, const int& y)
        {
            this->position.x=x;
            this->position.y=y;
            this->gameBoard[x][y]='K';
        }
        std::vector<Point> allowedMoves() const override;
        void setPosition(const Point&) override;
};