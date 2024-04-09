#pragma once
#include "Point.hpp"
#include <vector>
class GamePlayer{
    protected:
        Point position;
    public:
        static std::vector<std::vector<char>>gameBoard;
        Point getPosition() const;
        virtual void setPosition(const Point&)=0;
        virtual std::vector<Point> allowedMoves()const = 0;
};