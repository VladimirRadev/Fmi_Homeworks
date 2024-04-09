#include "Knight.hpp"
#include <cmath>
std::vector<Point> Knight::allowedMoves() const
{
    std::vector<Point> res;
    int rows = this->gameBoard.size();
    int cols = this->gameBoard[0].size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if(abs((double)this->position.x - i) <= 1  && abs((double)this->position.y-j)<=1 && gameBoard[i][j]=='0')
            {
                bool flag=true;
                for (int k = 0; k < rows; k++)
                {
                    for (int l = 0; l < cols; l++)
                    {
                        if(gameBoard[k][l]=='K' || gameBoard[k][l]=='S' )
                        {
                            continue;
                        }
                        if(abs((double)k - i) <= 1  && abs((double)l-j)<=1 && gameBoard[k][l]=='1')
                        {
                            flag=false;
                            break;
                        }
                    }
                    if(!flag)
                    {
                        break;
                    }
                    
                }
                if(flag)
                {
                res.push_back(Point(i,j));
                }
            }
        }
    }    
    
    return res;

}
void Knight::setPosition(const Point& rhs)
{
    this->position = rhs;
    this->gameBoard[rhs.x][rhs.y]='K';
}