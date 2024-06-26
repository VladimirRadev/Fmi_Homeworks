#include <iostream>
#include <cstring>

bool isValid(char c)
{
    return c > 32;
}
void print(const char* start, const char* end)
{

    while(start<= end)
    {
        std::cout<<*(start);
        start++;
    }
}
void print_backwards(const char* begin, const char* end)
{
    if(begin> end)
    {
        return;
    }
    const char* cur = end;
    while(isValid(*cur) && cur >= begin)
    {
        --cur;
    }
    
    print(cur + 1,end);
    while(!isValid(*cur) && cur >= begin)
    {
        --cur;
    }
    if(begin!= end)
    {
     std::cout<<' ';
    }
    print_backwards(begin,cur);
}
void print_backwards(const char* string)
{
    const char* ptr= string + strlen(string) - 1;
    print_backwards(string,ptr);
}

int main()
{
    print_backwards("I\tneed a break!");
}