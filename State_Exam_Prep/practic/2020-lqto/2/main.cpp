#include <iostream>
#include <vector>
#include <algorithm>

class Interval
{
protected:
    int a;
    int k;
    int reset_, last_;

public:
    Interval(const int &a, const int &k) : a(a), k(k), reset_(a), last_(a + k)
    {
    }
    Interval &operator=(const Interval &rhs)
    {

        this->a = rhs.a;
        this->k = rhs.k;
        this->reset_ = rhs.reset_;
        this->last_ = rhs.last_;
        return *this;
    }
    virtual int operator*()
    {
        return this->a;
    }
    // prefix
    Interval &operator++()
    {
        if (this->a != this->last_)
        {
            this->a++;
        }
        return *this;
    }
    // postfix
    Interval operator++(int)
    {
        Interval temp(*this);
        if (this->a != this->last_)
        {
            this->a++;
        }
        return temp;
    }
    void reset()
    {
        this->a = this->reset_;
    }
    bool last()
    {
        return this->a == this->last_;
    }
};

class SquaredInterval : public Interval
{
public:
    SquaredInterval(const int &a, const int &k) : Interval(a, k) {}
    SquaredInterval &operator=(const SquaredInterval &rhs)
    {
        Interval::operator=(rhs);
        return *this;
    }
    int operator*() override
    {
        return this->a * this->a;
    }
};
bool compare_(SquaredInterval lhs, SquaredInterval rhs)
{
    return *lhs < *rhs;
}
void sortSquared(std::vector<SquaredInterval> &vec)
{
    std::sort(vec.begin(), vec.end(), compare_);
}
int main()
{
    // a)
    //  Interval i(0, 10);
    //  std::cout << *i << std::endl;
    //  do
    //  {
    //      ++i;
    //      std::cout << *i << std::endl;
    //  } while (!i.last());

    // std::cout<<std::endl;

    // b)
    //  SquaredInterval l(0, 10);
    //  std::cout << *l << std::endl;
    //  do
    //  {
    //      ++l;
    //      std::cout << *l << std::endl;
    //  } while (!l.last());

    // c)

    std::vector<SquaredInterval> vec;
    vec.push_back(SquaredInterval(0, 2));
    vec.push_back(SquaredInterval(-3, 2));
    vec.push_back(SquaredInterval(2, 2));
    vec.push_back(SquaredInterval(1, 2));
    vec.push_back(SquaredInterval(10, 2));
    vec.push_back(SquaredInterval(-4, 2));


    sortSquared(vec);
    for (SquaredInterval x : vec)
    {
        std::cout << *x << std::endl;
    }
}