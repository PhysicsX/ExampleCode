#ifndef _EXAMPLEA_H_
#define _EXAMPLEA_H_

#include <iostream>
#include <memory>
#include "exampleAInt.h"
#include "exampleBInt.h"

class A :   public std::enable_shared_from_this<A>, public interfaceA
{
    public:
        A();
        
        void foo() ;

        void Acallback();
        
        std::shared_ptr<interfaceB> Bptr;
    
};

#endif