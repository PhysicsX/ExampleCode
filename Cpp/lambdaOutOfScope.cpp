#include <iostream>
#include <string>
#include <functional>

// Example of passing this to lambda expression
// that is not working for out of scope case for 
// dummy foo object

// should be used *this. It is available after c++17

struct foo
{
    int id;
    std::string name;
    //std::function<void(void)> run()
    auto run()
    {
        return[this]{ std::cout << id << ' ' << name << '\n'; };
        //return[*this]{ std::cout << id << ' ' << name << '\n'; };
    }
};

//std::function<void(void)> boo()
auto boo()
{
    return foo{ 42, "john" }.run();
}

int main()
{
    auto l = boo();
    l(); // does not print 42 john
}
