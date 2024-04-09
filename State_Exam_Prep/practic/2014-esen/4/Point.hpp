#pragma once
#include <string>
struct Point{
    int x,y;
    explicit Point(const int& x=-1 ,const int& y=-1);
    std::string stringify()const;
};