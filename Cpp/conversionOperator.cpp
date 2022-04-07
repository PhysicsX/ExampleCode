#include <iostream>
#include <string>

//how to use conversion operator
class smart;
class dummy
{
    dummy()=default;   
    public:
    friend class smart;
};

class smart
{
    public:
        dummy d;
        
        // conversion operator overloading
        operator dummy()
        {
            return d;
        }
};

int main()
{

    // possible usages
    // each line call the operator dummy() method
    dummy d = smart();
    
    smart s2;
    dummy d2 = s2;
    
    dummy d3 = smart().operator dummy();
    
    smart s3;
    dummy d5 = s3.operator dummy(); 
    
    auto s4 = smart();
    
}