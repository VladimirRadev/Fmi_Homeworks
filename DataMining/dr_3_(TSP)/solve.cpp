#include <iostream>
#include <cmath>
int main()
{
    double x1,x2,y1,y2;
    std::cin >> x1 >> y1;
    std::cin>> x2>> y2;
    std::cout << "Distance between Aberystwyth and Inverness is: " 
                <<sqrt(pow((x1-x2),2) + pow((y1-y2),2)) <<std::endl;
}