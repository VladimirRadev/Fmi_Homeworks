#include <iostream>
#include "Knight.hpp"
#include "SeaMonster.hpp"
std::vector<std::vector<char>> GamePlayer::gameBoard;
void allMoves(const std::vector<GamePlayer *> &players)
{

    for (size_t i = 0; i < players.size(); i++)
    {
        std::vector<Point> allowedMoves = players[i]->allowedMoves();
        Knight *isKnight = dynamic_cast<Knight *>(players[i]);
        SeaMonster *isSeaMonster = dynamic_cast<SeaMonster *>(players[i]);

        for (auto move : allowedMoves)
        {
            for (int j = 0; j < players.size(); j++)
            {
                if(players[i]!=players[j])
                {
                Point posJ = players[j]->getPosition();
                if ((abs((double)move.x - posJ.x ) <= 1 && abs((double)move.y - posJ.y) <= 1) )
                {
                    if (isKnight)
                    {
                        std::cout << "Knight " << isKnight->getPosition().stringify() << " -> " << move.stringify() << std::endl;
                    }
                    else if (isSeaMonster)
                    {
                        std::cout << "SeaMonster " << isSeaMonster->getPosition().stringify() << " -> " << move.stringify() << std::endl;
                    }
                }
                }
            }
        }
    }
}
int main()
{
    // Point a(20,21);
    // std::cout<<a.stringify()<<std::endl;
    // Point b(a);
    // std::cout<<b.stringify()<<std::endl;
    // b.x=19;
    // a=b;
    // std::cout<<a.stringify()<<std::endl;
    // std::cout<<b.stringify()<<std::endl;

    int x, y;
    std::cout << "Molq vuvedete razmeri na boarda: ";
    std::cin >> x >> y;
    std::vector<std::vector<char>> grid(x, std::vector<char>(y, 'x'));

    std::cout << "Molq vuvedete nachalno sustoqnie na boarda: \n";
    char l;
    for (size_t i = 0; i < x; i++)
    {
        for (size_t j = 0; j < y; j++)
        {
            std::cin >> l;
            grid[i][j] = l;
        }
    }
    std::cout << std::endl;
    GamePlayer::gameBoard = grid;

    // Knight k;
    // k.setPosition(Point(1,1));

    // for (size_t i = 0; i < x; i++)
    // {
    //     for (size_t j = 0; j < y; j++)
    //     {
    //        std::cout<<GamePlayer::gameBoard[i][j]<<' ';
    //     }
    //     std::cout<<std::endl;
    // }
    // std::cout<<std::endl;

    // std::vector<Point> allowed = k.allowedMoves();
    // for (auto x: allowed)
    // {
    //     std::cout<<x.stringify()<<' ';
    // }
    // std::cout<<std::endl;

    // SeaMonster sm(0,0);

    // for (size_t i = 0; i < x; i++)
    // {
    //     for (size_t j = 0; j < y; j++)
    //     {
    //        std::cout<<GamePlayer::gameBoard[i][j]<<' ';
    //     }
    //     std::cout<<std::endl;
    // }
    // std::cout<<std::endl;

    // std::vector<Point> allowed = sm.allowedMoves();
    // for (auto x: allowed)
    // {
    //     std::cout<<x.stringify()<<' ';6 
    // }
    // std::cout<<std::endl;

    std::vector<GamePlayer *> vec = {
        new Knight(1, 2),
        new SeaMonster(0, 0),
        new SeaMonster(3,0),
        };

    for (size_t i = 0; i < x; i++)
    {
        for (size_t j = 0; j < y; j++)
        {
            std::cout << GamePlayer::gameBoard[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    allMoves(vec);
}