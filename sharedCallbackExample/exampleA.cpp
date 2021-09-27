
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include "exampleB.h"
#include "exampleA.h"


A::A()
{
    std::cout<<"A cons"<<std::endl;
    //Bptr = std::make_shared<B>(shared_from_this()); // can not be called inside of the constructor

    // std::thread([this](){

    //     std::this_thread::sleep_for (std::chrono::seconds(1));
    //     Bptr = std::make_shared<B>(shared_from_this());

    // }).detach();
    
    //std::this_thread::sleep_for (std::chrono::seconds(3));

}

void A::foo()
{
    Bptr = std::make_shared<B>(shared_from_this()); // can not be called inside of the constructor
    //It is permitted to call shared_from_this only on a previously shared object, i.e. on an object managed by std::shared_ptr (in particular, shared_from_this cannot be called during construction of *this).
    // terminate called after throwing an instance of 'std::bad_weak_ptr
}

void A::Acallback()
{
    std::cout<<"Acallback"<<std::endl;
}


