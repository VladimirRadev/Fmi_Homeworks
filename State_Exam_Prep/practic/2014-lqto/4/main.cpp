#include <iostream>
#include "Rook.hpp"
#include "Knight.hpp"
#include <map>

void allMoves(std::vector<ChessPiece*> pieces)
{
    for (auto iter = pieces.begin(); iter != pieces.end(); iter++)
    {
        ChessPosition curPos = (*iter)->getPosition();
        ChessPosition& curPosToMove = (*iter)->getPosition();
        std::vector<ChessPosition> curAllowedMoves = (*iter)->allowedMoves();
        for (auto j = curAllowedMoves.begin(); j != curAllowedMoves.end(); j++)
        {
            curPosToMove=(*j);
            bool flag=true;
            for (auto iter2 = pieces.begin(); iter2 != pieces.end(); iter2++)
            {
                //we check different pieces than current
                if(iter!=iter2)
                {
                    if((*iter2)->captures(*j))
                    {
                        flag=false;
                        break;
                    }
                }
                continue;
            }
            if(flag)
            {
                Rook* isRook = dynamic_cast<Rook*>((*iter));
                if(isRook)
                {
                    std::cout<<"Rook "<<curPos.d1<<curPos.d2<<" -> "<<(*iter)->getPosition().stringify()<<std::endl;
                }
                else // it is knight
                {
                    std::cout<<"Knight "<<curPos.d1<<curPos.d2<<" -> "<<(*iter)->getPosition().stringify()<<std::endl;
                    
                }
            }
            curPosToMove=curPos;
        }
    }
}

int main()
{
    std::vector<ChessPiece*> vec = {
        new Rook('A',1),
        new Knight('B',3)
    };
    allMoves(vec);
}
