#ifndef _EXAMPLEB_H_
#define _EXAMPLEB_H_

#include <iostream>
#include <memory>
#include "exampleBInt.h"
#include "exampleA.h"

class B : public interfaceB, public std::enable_shared_from_this<B>
{
    public:
        B(std::shared_ptr<A> Aptr);
        void fooB() override;

    std::shared_ptr<A> mAptr;
    
};

#endif