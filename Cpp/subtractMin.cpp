#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

int main()
{
    std::vector<int> vec;
    int size = 10000000;
    for(int i=0; i<size; ++i)
    {
        vec.push_back(1);
    }

    vec[vec.size()-1] = 2;

    auto begin = std::chrono::steady_clock::now();

    const auto max = *std::max_element(std::begin(vec), std::end(vec));
    
    long long res=0;
    for(const auto x : vec)
        res += x;

    res = res - max;

    auto end = std::chrono::steady_clock::now();
    std::cout<<"result "<<res<<std::endl;
    std::cout<<"diff "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()<<" [ns]"<<std::endl;
    
    res = 0;
    int maxElement = 0;

    begin = std::chrono::steady_clock::now();

    for(int i=0; i<size; ++i)
    {
        res += std::min(maxElement, vec[i]);
        maxElement = std::max(maxElement, vec[i]);
    }
    
    end = std::chrono::steady_clock::now();
    std::cout<<"result "<<res<<std::endl;
    std::cout<<"diff "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()<<" [ns]"<<std::endl;

    // Time complexity of two approaches are O(n), But this does not mean they will consume same time. 
    // Second one is more faster than the first one. Becuase there is only one for loop.

}