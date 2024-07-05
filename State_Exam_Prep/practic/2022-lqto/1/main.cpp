#include <iostream>
using std::cout;

bool isEven(unsigned int);
bool isOdd(unsigned int n)
{
    if (n == 0)
        return false;
    if (n == 1)
        return true;
    return isEven(n - 1);
}
bool isEven(unsigned int n)
{
    if (n == 0)
        return true;
    if (n == 1)
        return false;
    return isOdd(n - 1);
}

int main()
{
    cout << std::boolalpha << isOdd(0) << '\n';
    cout << std::boolalpha << isOdd(1) << '\n';
    cout << std::boolalpha << isEven(0) << '\n';
    cout << std::boolalpha << isEven(1) << '\n';
    cout << std::boolalpha << isEven(20) << '\n';
    cout << std::boolalpha << isEven(21) << '\n';
    cout << std::boolalpha << isOdd(20) << '\n';
    cout << std::boolalpha << isOdd(21) << '\n';

    switch (5 % 2)
    {
    case 0:
        std::cout << "0";
    case 1:
        std::cout << "1";
    default:
        std::cout << "x";
    }
}
