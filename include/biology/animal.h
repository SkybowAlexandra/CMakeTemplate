#pragma once
#include <iostream>
#include <concepts>
#include <type_traits>

namespace biology
{
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


    template <typename T>
    concept ANIMAL = requires(T t) {
        std::is_class_v<T>;
    };

    template <ANIMAL T>
    class Animal : public T
    {
    public:
        Animal() : T()
        {
            std::cout << "Animal constructor" << std::endl;
        }
        virtual ~Animal()
        {
            std::cout << "Animal destructor" << std::endl;
        }
        void Speak()
        {
            T::Speak();
        }
    };

}
