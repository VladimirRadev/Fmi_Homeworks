#include <iostream>

void selection_sort(int* arr, const size_t& size)
{
    for (size_t i = 0; i < size-1; i++)
    {
        size_t min_ind=i;
        for (size_t j = i+1; j < size; j++)
        {
            if(arr[j]<arr[min_ind])
            {
                min_ind=j;
            }
        }
        if(min_ind!=i)
        {
            std::swap(arr[i],arr[min_ind]);
        }
        
    }
    

}
void insertion_sort(int* arr, const size_t& size)
{
    for (size_t i = 1; i < size; i++)
    {
        const int cur_val=arr[i];
        size_t ind=i;
        while (ind > 0 && arr[ind-1] > cur_val)
        {
            arr[ind]=arr[ind-1];
            --ind;
        }
        arr[ind]=cur_val;
    }
    
    
}
void buble_sort(int* arr, const size_t& size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        bool is_swapped = false;
        for (size_t j = 0; j < size - 1 - i; j++)
        {
            if(arr[j] > arr[j+1])
            {
                std::swap(arr[j],arr[j+1]);
                is_swapped=true;
            }
        }
        if(!is_swapped)
        {
            break;
        }
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
    selection_sort(arr,size);
    std::cout<<"Selection sort\n";
    for (size_t i = 0; i < size; i++)
    {
        std::cout<<arr[i]<<' ';   
    }
    std::cout<<'\n';

    // insertion_sort(arr,size);
    // std::cout<<"Insertion sort\n";
    // for (size_t i = 0; i < size; i++)
    // {
    //     std::cout<<arr[i]<<' ';   
    // }
    // std::cout<<'\n';

    // buble_sort(arr,size);
    // std::cout<<"Buble sort\n";
    // for (size_t i = 0; i < size; i++)
    // {
    //     std::cout<<arr[i]<<' ';   
    // }
    // std::cout<<'\n';

    delete[] arr;
}