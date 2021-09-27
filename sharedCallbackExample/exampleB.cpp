#include <iostream>
#include <memory>
#include "exampleB.h"
#include "exampleA.h"


B::B(std::shared_ptr<A> Aptr)
{
    std::cout<<"B const"<<std::endl;
    Aptr->Acallback();
}

void B::fooB()
{

}