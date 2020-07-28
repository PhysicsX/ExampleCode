
#include <iostream>

using namespace std;

template <typename A, typename B>
auto findMin(A a, B b) -> decltype( (a < b) ? a: b) // decltype is not necessary for c++14
{
        return (a < b) ? a : b;
}

auto foo(int a, double b)
{
  return (a < b) ? a : b;
}

int main()
{

    std::cout<<findMin(3.14, 4)<<std::endl;
    
    //check the return type is dobule or not
    std::cout << std::is_same<double, decltype(findMin(3.14, 4))>::value<<std::endl;
    std::cout << std::is_same<int, decltype(findMin(3.14, 4))>::value<<std::endl;

    return 0;
}