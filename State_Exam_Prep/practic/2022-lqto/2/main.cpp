#include <iostream>
using namespace std;
class A
{
public:
    A() { cout << "A()\n"; }
    A(A &) { cout << "A(A&)\n"; }
    virtual ~A() { cout << "~A()\n"; }
    A &operator=(A &)
    {
        cout << "op=(A&)\n";
        return *this;
    }
};
class B : public A
{
public:
    B() { cout << "B()\n"; }
    B(B &) { cout << "B(B&)\n"; }
    virtual ~B() { cout << "~B()\n"; }
    B &operator=(B &)
    {
        cout << "op=(B&)\n";
        return *this;
    }
};
void f(A b) { cout << "f(A)\n"; }
int main()
{

B d;

B copy = d;

A b = d;


A& ref = d;

B arr[2];

f(d);


A* p = new B(d);


delete p;


d = d;


ref = d;


}