#include <iostream>

int reverseInteger(int n)
{
    int reversed {0};

    while(n)
    {
        int reminder = n%10;

        reversed = reversed * 10 + reminder;
        n /= 10;
    }

    return reversed;
}


int main()
{
    int n = 12345;
    std::cout<<reverseInteger(n);

    return 0;
}