#include <iostream>
#include <cstring>
int main()
{
    // int arr[] = {1,2,3};
    // std::cout<<std::boolalpha<<(arr[1] == *(arr+2))<<'\n';
    // std::cout<<std::boolalpha<<(arr == &arr[0])<<'\n';
    // std::cout<<std::boolalpha<<((arr + 1) == &arr[1])<<'\n';
    // std::cout<<std::boolalpha<<(*arr == arr[0])<<'\n';

    char s1[]="Hello";
    char s2[]="world!";
    char result[80];

    strcpy(result,s1);
    strcat(result," ");
    strcat(result,s2);

    std::cout<<result<<'\n';


}