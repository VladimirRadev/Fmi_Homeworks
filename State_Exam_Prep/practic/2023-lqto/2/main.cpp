#include <iostream>
#include <vector>
#include <iostream>
template <typename T>
class Function
{
public:
    virtual T value(T) const = 0;
};

class Inc : public Function<double>
{
public:
    double value(double x) const { return x + 1; }
};
class Square: public Function<double>
{
public:
    double value(double x) const { return x * x; }
};

template <typename T>
class Max: public Function<T>
{
private:
    std::vector<Function<T>*> functions;

public:
    void addFunction(Function<T>* f)
    {
        functions.push_back(f);
    }
    T value(T x) const
    {
        if (functions.empty())
            throw "Function list is empty!";
        T max = functions[0]->value(x);
        for(Function<T>* func: functions)
        {
            if (func->value(x) > max)
            {
                max=func->value(x);
            }
        }
        return max;
    }
};
template <typename T>
class Sum: public Function<T>
{
private:
    std::vector<Function<T>*> functions;

public:
    void addFunction(Function<T>* f)
    {
        functions.push_back(f);
    }
    T value(T x) const
    {
        T sum = {0.0};
        for(Function<T>* func: functions)
        {
            sum+=func->value(x);
        }
        
        return sum;
    }
};
int main()
{
    Inc i;
    Square sq;
    Sum<double> s;
    //(x+1)+(x*x)
    s.addFunction(&i);
    s.addFunction(&sq);
    Max<double> m;
    //{x+1, x*x, (x+1)+(x*x)}
    m.addFunction(&i);
    m.addFunction(&sq);
    m.addFunction(&s);
    double x;
    std::cin >> x;
    std::cout << m.value(x) << std::endl;
}
