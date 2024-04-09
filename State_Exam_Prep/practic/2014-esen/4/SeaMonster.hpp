#pragma once
#include "GamePlayer.hpp"
class SeaMonster : public GamePlayer
{
    public:
        SeaMonster(const int& x, const int& y)
        {
            this->position.x=x;
            this->position.y=y;
            this->gameBoard[x][y]='S';
        }
        std::vector<Point> allowedMoves() const override;
        void setPosition(const Point&) override;
};