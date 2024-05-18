#include <iostream>
#include <string.h>
int findPosOfEmployee(const char *employee, const char *leaders[][2], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (strcmp(employee, leaders[i][0]) == 0)
        { 
            return (int)i;
        }
    }
    return -1;
}

bool is_subordinate(const char *employee, const char *manager, const char *leaders[][2], size_t n)
{
    int pos = findPosOfEmployee(employee, leaders, n);
    if (pos == -1)
    {
        return false;
    }
    if (strcmp(leaders[pos][1], manager) == 0)
    {
        return true;
    }
    return is_subordinate(leaders[pos][1],manager,leaders,n);
}
const char* the_big_boss(const char* leaders[][2],size_t n)
{
    const char* employee=leaders[0][0];
    int p;
    while ((p = findPosOfEmployee(employee,leaders,n) )!= -1)
    {
        employee=leaders[p][1];
    }
    return employee;
    
}

int main()
{
    const char *leaders[3][2] = {
        {"Иван Иванов", "Мария Иванова"},
        {"Мария Иванова", "Иван Драганов"},
        {"Иван Драганов", "Стоян Петров"}};
    // for(int i=0;i<3;i++)
    // {
    //     for (int j=0;j<2;j++)
    //     {
    //         std::cout<<leaders[i][j]<<' ';
    //     }
    //     std::cout<<'\n';
    // }

    std::cout << std::boolalpha << is_subordinate("Иван Иванов", "Мария Иванова", leaders, 3); //true
    std::cout<<'\n';
    std::cout << std::boolalpha << is_subordinate("Иван Иванов", "Иван Драганов", leaders, 3); //true
    std::cout<<'\n';
    std::cout << std::boolalpha << is_subordinate("Иван Иванов", "Стоян Петров", leaders, 3); //true
    std::cout<<'\n';
    std::cout << std::boolalpha << is_subordinate("Иван Драганов", "Мария Иванова", leaders, 3); //false
    std::cout<<'\n';

    std::cout<<the_big_boss(leaders,3);
}