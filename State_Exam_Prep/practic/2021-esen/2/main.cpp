#include <iostream>
using std::cout;
class test
{
public:
    int var;
    test()
    {
        cout << "test()\n";
        var = 0;
    }
    test &operator=(const test &other)
    {
        if (this != &other)
        {
            cout << "copy\n";
            var = other.var;
        }
        else
        {
            cout << "self-assignment\n";
        }
        return *this;
    }
    static test &instance()
    {
        static test obj;
        return obj;
    }
    test &self() { return *this; }
    void _oncreate() { cout << "_oncreate()\n"; }
    void _oncopy() { cout << "_oncopy()\n"; }
};
int main()
{
    test &r1 = test::instance(); // 1  // test()
    test &r2 = test::instance(); // 2  // нищо , r1 i r2 sochat kum edin i susht obekt, static test obj, toi edin
    r1.var = 10;                 // 3  // нищо
    cout << r2.var << "\n";      // 4  // 10 ( понеже r1 i r2 сочат към obj , то като променяме единия променяме и другия)
    r1.self() = r2;              // 5  // self-assignment / zashtoto r1 i r2 сочат kym obj ,една и съща памет
    new test[3];                 // 6 // test()\ntest()\ntest() , 3 puti defaultniq konstructor no nishto ne catchva taq dinamichna pamet
}

