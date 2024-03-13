#include <iostream>
#include <memory>
#include <string>
#include <func/CallbackHandler.h>
#include <biology/animal.h>

using namespace biology;
using namespace func;

template <typename T>
T add(T a, T b)
{
    return a + b;
}


int main(int argc, char *argv[])
{
    Callback<int> c;
    c.register_func(add<int>, 5, 2);
    auto ret = c.call();
    std::cout << ret << std::endl;

    Callback<void> c2;
    c2.register_func([](int a, int b)->void{std::cout << 2*3 << std::endl;},2,3);
    c2.call();
    Animal<Cat> cat;
    cat.Speak();


    return 0;
}
