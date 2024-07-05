class foo {
public:
foo(int) {}
};
void g(foo) {}
void f(int) {}

int main()
{
    g(5);
    //f(foo(5));
    foo('a');
}