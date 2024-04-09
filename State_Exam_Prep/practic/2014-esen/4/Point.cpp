#include "Point.hpp"
Point::Point(const int& x , const int& y):x(x),y(y){}
std::string Point::stringify()const
{
    std::string res;
    res+='(';
    res+=std::to_string(this->x);
    res+=',';
    res+=std::to_string(this->y);
    res+=')';
    return res;
}   
