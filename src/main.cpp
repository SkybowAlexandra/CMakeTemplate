#include <iostream>
#include <memory>
#include <string>
#include <biology/animal.h>

using namespace biology;


int main(int argc, char *argv[])
{
    std::shared_ptr<Animal<Cat>> cat = std::make_shared<Animal<Cat>>();
    cat->Speak();

}
