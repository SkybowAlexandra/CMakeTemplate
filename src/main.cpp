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


int test()
{
    return int{};
}

int main(int argc, char *argv[])
{
    Callback<int> c;
    c.register_func(add<int>, 5, 2);
    auto ret = c.call();
    std::cout << ret << std::endl;

    return 0;
}
