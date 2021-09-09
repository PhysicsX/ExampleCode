/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <string>
#include <mutex>
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <thread>
#include <chrono>

struct X {
    int operator()(int i) {
        
        std::cout << i << '\n';
        return i + 10;
    }
};

template<typename T>
class my_queue
{
    
private:
    std::queue<T> m_queque;
    mutable std::mutex m_mutex;
    
public:
    void push(T& value )
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queque.push(std::move(value));
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queque.pop();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queque.empty();
    }
    
    std::future<int> front()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return std::move(m_queque.front());
    }

    int size()
    {
        return m_queque.size();
    }

};



int main()
{
    
    my_queue<std::future<int>> q;
    
    auto a = std::async(std::launch::async,X(), 1);
    
    q.push(a);
    
    if(!q.empty())
    {
        std::thread([&](){
            
            // empty returns true if container size is 0
            
            std::this_thread::sleep_for(std::chrono::milliseconds(4000));
            std::cout<<std::endl;
            std::cout<<"----------------------------"<<q.size()<<std::endl;
            std::cout<<"size "<<q.size()<<std::endl;

            while(!q.empty())
            {
                auto p = q.front();
                q.pop();
                    try {
                        std::cout<<p.get()<<std::endl;
                    }
                    catch (std::exception&) {
                        std::cout << "[exception caught]";
                    }
            }
            
        }).detach();
    }
    
    for( int i = 2; i < 100; i++)
    {
        auto b = std::async(std::launch::async,X(), i);
        
        q.push(b);
    }
    
    //auto c = std::async(std::launch::async,X(), 3);
    
    //q.push(std::move(c));
  
    
            std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    
    //std::cout << a.get() << '\n';
    
    return 0;
}
