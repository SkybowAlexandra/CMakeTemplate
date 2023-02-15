#pragma once
#include <iostream>
#include <concepts>
#include <type_traits>


namespace biology
{
template<typename T>
concept Animal =  requires (T animal)
{
    std::is_pointer_v<T>;
    animal->Speak();
};

template <Animal T>
static void Speak(T animal)
{
    animal->Speak();
}

class Dog final
{
public:
    Dog() = default;
};

class Cat final
{
public:
    Cat() = default;
    void Speak() const;
};
}