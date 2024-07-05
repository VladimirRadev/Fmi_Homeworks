#include <iostream>
class base
{
public:
    base() { std::cout << "base::base()\n"; }
    ~base() { std::cout << "base::~base()\n"; }
    virtual void f() { std::cout << "base::f()\n"; };
};
class derived : public base
{
public:
    derived() { std::cout << "derived::derived()\n"; }
    ~derived() { std::cout << "derived::~derived()\n"; }
    virtual void f() { std::cout << "derived::f()\n"; }
};
int main()
{
    base *p = new derived(); // 1
    p->f();                  // 2
    base obj = *p;
    obj.f();  // 3
    delete p; // 4
}

//
// base::base()
// derived::derived()
// derived::f()
// base::f()
// base::~base()
// base::~base()
