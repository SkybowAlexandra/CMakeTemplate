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

    c.register_func([](int a, int b)
                    { std::cout << "a+b: " << a + b << std::endl; return 0; },
                    5, 3);
    c.call();

    std::shared_ptr<Animal<Cat>> cat = std::make_shared<Animal<Cat>>();
    cat->Speak();
    return 0;
}
