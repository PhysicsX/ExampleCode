#include <iostream>

using namespace std;

class Example{

    public:

    int ctr = 0;

    void increase(int value)
    {
        ctr += value;
    }

    void decrease(int value)
    {
        ctr -= value;
    }
};