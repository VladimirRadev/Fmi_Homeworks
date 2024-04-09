#include "SeaMonster.hpp"
std::vector<Point> SeaMonster::allowedMoves() const
{
    int rows = this->gameBoard.size();
    int cols = this->gameBoard[0].size();

    std::vector<Point> res;
    //horizontal
    for (int i = 0; i < rows; i++)
    {
        if(i!=this->position.x)
        {
            continue;
        }
        for (int j = this->position.y - 1 ; j >=0 ; j--)
        {
            if(this->gameBoard[i][j]=='2')
            {
                res.push_back(Point(i,j));
            }
            else
            {
                break;
            }
        }
        for (int j = this->position.y + 1 ; j < cols ; j++)
        {
            if(this->gameBoard[i][j]=='2')
            {
                res.push_back(Point(i,j));
            }
            else
            {
                break;
            }
        }
        
    }
     //vertical
    for (int j = 0; j < cols; j++)
    {
        if(j!=this->position.y)
        {
            continue;
        }
        for (int i = this->position.x-1; i >= 0; i--)
        {
            if(this->gameBoard[i][j]=='2')
            {
                res.push_back(Point(i,j));
            }
            else
            {
                break;
            }
        }
        for (int i = this->position.x+1; i < rows; i++)
        {
            if(this->gameBoard[i][j]=='2')
            {
                res.push_back(Point(i,j));
            }
            else
            {
                break;
            }
        }
        
    }
    
    return res;
}
void SeaMonster::setPosition(const Point& rhs)
{
    this->position=rhs;
    this->gameBoard[rhs.x][rhs.y]='S';
}