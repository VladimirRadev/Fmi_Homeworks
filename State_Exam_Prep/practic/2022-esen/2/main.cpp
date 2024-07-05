#include <iostream>

// class test
// {
// public:
//     virtual void f() = 0;
//     virtual ~test()
//     {
//         std::cout << "test::~test()\n";
//     }
// };
// class derived : public test
// {
// public:
//     void f() override
//     {
//         std::cout << "derived::f()\n";
//     }
//     ~derived() override
//     {
//         std::cout << "derived::~derived()\n";
//     }
// };

template<typename T> 
class Array
{
        static const size_t size = 10;
        T data[size];

    public:
        T& at(size_t index)
        {
            if (index >= size)
                throw std::out_of_range("error");
            return data[index];
        }
};
void test()
{
    Array<int> a;
    a.at(0) = 5;
    std::cout << a.at(0);
    Array<Array<int>> b;
    b.at(0) = a;
    std::cout << b.at(0).at(0);
}

int main()
{
    // test *ref = new derived();
    // test &id = *ref;
    // delete ref;

    test();
}