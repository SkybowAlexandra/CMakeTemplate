#include <iostream>
#include <biology/animal.h>
using namespace biology;

int main(int argc, char *argv[])
{
    Cat *cat = new Cat;
    Speak(cat);
    delete cat;
    return 0;
}
