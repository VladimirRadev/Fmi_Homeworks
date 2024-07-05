#include <iostream>

// bool isWhitespace(char c)
// {
//     return c == ' ' || c == '\t' ||
//            c == '\r' || c == '\n';
// }
// char *removeWhitespace(char *str)
// {
//     size_t read = 0, write = 0;
//     while (str[read])
//     {
//         if (isWhitespace(str[read]))
//             read++;
//         else
//             str[write++] = str[read++];
//     }
//     str[write] = '\0';
//     return str;
// }

// void pass(int *arr,
//           size_t size,
//           bool &swappedAtLeastOnce)
// {
//     if (size <= 1)
//         return;
//     if (arr[0] > arr[1])
//     {
//         std::swap(arr[0], arr[1]);
//         swappedAtLeastOnce = true;
//     }
//     pass(arr + 1,
//             size - 1,
//            swappedAtLeastOnce);
// }
// void bubbleSort(int *arr, size_t size)
// {
//     bool swappedAtLeastOnce = false;
//     pass(arr, size, swappedAtLeastOnce);
//     if (swappedAtLeastOnce)
//         bubbleSort(arr, size);
// }
int main()
{
    // char str[] = "abc";
    // char *p = str;
    // ++p;
    // ++*p;
    // // std::cout<<*p++<<std::endl;
    // // std::cout<<*p<<std::endl;
    // std::cout << str;

    // int arr[] = {5,1,0};
    // bubbleSort(arr,3);

    // for (int i = 0; i < 3; i++)
    // {
    //     std::cout<<arr[i]<<' ';
    // }
    // std::cout<<'\n';
    
}