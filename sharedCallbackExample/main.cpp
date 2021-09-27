
#include <iostream>
#include <string>
#include <memory>
#include "exampleA.h"

//g++ -std=c++17 main.cpp exampleA.cpp exampleB.cpp -lpthread

int main()
{
    std::shared_ptr<interfaceA> Aptr { std::make_shared<A>() };
    Aptr->foo();

    while(1);
}