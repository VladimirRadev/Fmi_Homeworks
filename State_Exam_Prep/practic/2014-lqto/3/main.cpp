#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include <algorithm>

int partition(float* arr, int low,int high)
{
    float pivot= arr[high];
    int i=(low-1);

    for (size_t j = low; j <= high; j++)
    {
        if(arr[j]<pivot)
        {
            i++;
            std::swap(arr[i],arr[j]);
        }
    }
    std::swap(arr[i+1],arr[high]);
    return (i+1);
}

void quickSort(float* arr, int low, int high)
{
    if(low<high)
    {
        int pi=partition(arr,low,high);
        quickSort(arr,low, pi-1);
        quickSort(arr,pi+1,high);
    }
}

const int MAX_NUMBER = 4900;
const float ALPHA = 0.000001f;
const float DELTA = 0.00000001f;
int main()
{
    std::srand(std::time(nullptr));

    float A[27] = {};

    for (size_t i = 0; i < 27; i++)
    {
        float cur = (float)std::rand();
        A[i] = ((float)(std::rand() % MAX_NUMBER) / 1000.0) + ALPHA;
    }

    float under1[27] = {};
    float under2[27] = {};
    float under3[27] = {};
    float under4[27] = {};
    float under5[27] = {};

    int u1 = 0, u2 = 0, u3 = 0, u4 = 0, u5 = 0;
    for (size_t i = 0; i < 27; i++)
    {
        if (A[i] < 1.0 )
        {
            under1[u1++] = A[i];
        }
        else if (A[i] < 2.0 )
        {
            under2[u2++] = A[i];
        }
        else if (A[i] < 3.0 )
        {
            under3[u3++] = A[i];
        }
        else if (A[i] < 4.0 )
        {
            under4[u4++] = A[i];
        }
        else if (A[i] < 5.0 )
        {
            under5[u5++] = A[i];
        }
    }
    quickSort(under1,0,u1-1);
    quickSort(under2,0,u2-1);
    quickSort(under3,0,u3-1);
    quickSort(under4,0,u4-1);
    quickSort(under5,0,u5-1);

    std::vector<int> vec={u1,u2,u3,u4,u5};
    auto iter= std::max_element(vec.begin(),vec.end());

    std::cout << std::setw(12) << std::left <<"Под 1"<< std::setw(12) << std::left <<"Под 2" 
    << std::setw(12) << std::left <<"Под 3"<< std::setw(12)<< std::left <<"Под 4" 
    << std::setw(12) << std::left <<"Под 5";
    std::cout<<std::endl;
    for (size_t i = 0; i < *iter; i++)
    {
        //equal to zero (non assigned value)
        if(abs(under1[i]-0.0) < DELTA)
        {
            std::cout<<std::setw(8)<<std::right<<"";
        }
        else
        {
            std::cout<<std::setw(8)<<std::right<<std::fixed << std::setprecision(4)<<under1[i];
        }

        //equal to zero (non assigned value)
        if(abs(under2[i]-0.0) < DELTA)
        {
           std::cout<<std::setw(8)<<std::right<<"";
        }
        else
        {
            std::cout<<std::setw(8)<<std::right<<std::fixed << std::setprecision(4)<<under2[i];
        }
        //equal to zero (non assigned value)
        if(abs(under3[i]-0.0) < DELTA)
        {
            std::cout<<std::setw(8)<<std::right<<"";
        }
        else
        {
            std::cout<<std::setw(8)<<std::right<<std::fixed << std::setprecision(4)<<under3[i];
        }
        //equal to zero (non assigned value)
        if(abs(under4[i]-0.0) < DELTA)
        {
           std::cout<<std::setw(8)<<std::right<<"";
        }
        else
        {
            std::cout<<std::setw(8)<<std::right<<std::fixed << std::setprecision(4)<<under4[i];
        }
        //equal to zero (non assigned value)
        if(abs(under5[i]-0.0) < DELTA)
        {
           std::cout<<std::setw(8)<<std::right<<"";
        }
        else
        {
            std::cout<<std::setw(8)<<std::right<<std::fixed << std::setprecision(4)<<under5[i];
        }
        std::cout<<std::endl;
    }
    

}