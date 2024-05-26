#include <iostream>
#include <memory>
#include <string>
#include <func/CallbackHandler.h>
#include <biology/animal.h>
#include <func/Global.h>
#include <func/Factory.h>

// import print_hello;

using namespace biology;
using namespace func;

template <typename T>
T add(T a, T b)
{
    return a + b;
}
class Cat
{
public:
    Cat()
    {
        std::cout << "Cat Constructor" << std::endl;
    }
    ~Cat()
    {
        std::cout << "Cat destructor" << std::endl;
    }
    void Speak()
    {
        std::cout << "Cat Speak" << std::endl;
    }
};
class Dog
{
public:
    Dog()
    {
        std::cout << "Dog Constructor" << std::endl;
    }
    ~Dog()
    {
        std::cout << "Dog destructor" << std::endl;
    }
    void Speak()
    {
        std::cout << "Dog Speak" << std::endl;
    }
};

int main()
{
    /*�ص������*/
    Callback<int> c;
    c.register_func(add<int>, 5, 2);
    auto ret = c.call();
    std::cout << ret << std::endl;

    Callback<void> c2;
    c2.register_func([](int a, int b) -> void
                     { std::cout << 2 * 3 << std::endl; },
                     2, 3);
    c2.call();

    /*����̬����*/
    Animal<Cat> cat;
    cat.Speak();

    /*ȫ�������*/
    Global<Dog>::New();
    Global<Dog>::Get()->Speak();
    Global<Dog>::Delete();

    /*���������*/
    auto c3 = Factory<Cat>::Create();
    c3->Speak();

    return 0;
}