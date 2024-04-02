#pragma once
#include <string>
struct ChessPosition{

    char d1;
    int d2;

    ChessPosition();
    ChessPosition(char d1, int d2);

    char getD1()const;
    int getD2()const;
    
    std::string stringify()const;
    bool operator==(const ChessPosition&other)const;


};