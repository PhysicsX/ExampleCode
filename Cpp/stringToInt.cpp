#include <string>
#include <iostream>
#include <climits>

int stringToInteger(const std::string& str)
{
    int result = 0;
    bool isNegative = false;
    int i = 0;

    //check str is negative or not
    if(str[0] == '-')
    {
        isNegative = true;
        i++;
    }

    for(; i<str.size(); ++i)
    {
        if(std::isdigit(str[i]))
        {

            // to check the overflow is exist or not
            // if INT_MAX > (result * 10 + (str[i] - '0')) then there is a overflow
            // if(result * 10 + (str[i] - '0') > INT_MAX) // but this will not work
            // because result * 10 + (str[i] - '0') if result is cause overflow then there
            // will be undefined behaviour so it is good idea to compare it with result

            if(result > (INT_MAX - (str[i] - '0')) / 10)
            {
                std::cout<<"overflow detected"<<std::endl;
                return isNegative ? INT_MIN : INT_MAX;
            }

            result = result * 10 + (str[i] - '0');
        }
        else
            return 0;
    }

    if(isNegative)
        result = -result;

    return result;
}

int main()
{
    std::cout<<stringToInteger("123")<<std::endl;
    std::cout<<stringToInteger("99999999999999999999999999");

    std::endl(std::cout);

    return 0;
}