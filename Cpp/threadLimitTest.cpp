
#include <iostream>
#include <thread>
#include <chrono>         // std::chrono::seconds
#include <atomic>
//g++ -std=c++17 threadLimitTest.cpp -lpthread -o binary

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
    std::atomic<int> a = 1;
    //for(int i = 0; i<100000; i++)
    try
    {
        while(a > 0)
        {
            
            std::thread([&](){
                
                    
                    while(1)
                    {
                            //a ++;
                            //std::cout<<a<<std::endl;
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    }
                
                }).detach();
                a ++;
        }
            
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "max number of threads "<<a<<'\n';
        return 0; // if uncomment this return, then although the error, progrma will continue
    }

    while(1);

}