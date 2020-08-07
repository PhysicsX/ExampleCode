#include <iostream>


int main()
{
        std::string str = "hello world";
        std::string str2 = "l";
        
        std::size_t pos = str.find(str2);
        
        while(pos != std::string::npos)
        {
                std::cout<<"found"<<std::endl;
                std::cout<<pos<<std::endl;
                pos = str.find(str2, pos + str2.size());
        }
}