#include <iostream>

//without final keyword inheritance

class A
{

    
    private:
        A(){};
        friend class B;
    
};

class B :  virtual public A
{

    
};

class C : public B
{

    
};

int main()
{
    
        C c;
        
        return 0;
    
}