#include <iostream>

int partition(int* arr, int low , int high)
{
    int pivot= arr[high];

    int i=(low-1);
    for (int j = low; j <= high; j++)
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
void quick_sort(int* arr, int low, int high)
{
    if(low<high)
    {
        int pi= partition(arr,low,high);

        quick_sort(arr,low,pi-1);
        quick_sort(arr,pi+1,high);
    }
}
int main()
{
    size_t size=0,k;
    std::cout<<"Vuvedi size: ";std::cin>>size;
    std::cout<<"Vuvedi elementi: ";

    int* arr= new int[size];
    
    for (size_t i = 0; i < size; i++)
    {
        std::cin>>k;
        arr[i]=k;
    }
    quick_sort(arr,0,size-1);
    std::cout<<"Quick Sort\n";
    for (size_t i = 0; i < size; i++)
    {
        std::cout<<arr[i]<<' ';   
    }
    std::cout<<'\n';

    delete[] arr;
}