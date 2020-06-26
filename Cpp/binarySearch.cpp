#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>
#include <unordered_map>
#include <chrono>

template <typename C>
void print(const C& container)
{
    for(const auto& val: container)
        std::cout<<val<<' ';
    std::cout<<'\n';
}

int main()
{
    std::vector<int> numbers(100);
    std::generate(numbers.begin(), numbers.end(),[](){

        static std::mt19937 rng(std::time(nullptr));
        return std::uniform_int_distribution<>(1,100)(rng);

    });

    std::cout<<"Here are the sorted numbers:\n";
    print(numbers);

    std::unordered_map<int,int> map;
    for(int i = 0; i<numbers.size();i++)
        map[numbers[i]]++;

    std::cout<<"Map size"<<map.size()<<"\n";

    std::vector<int> vec;
    
    for(auto it = map.begin(); it != map.end(); ++it)
        if(it->second > 0)
            vec.push_back(it->first);

    print(vec);

    std::cout<<"After sorting\n";
    std::sort(vec.begin(), vec.end());
    print(vec);

    int target = 55;
    int left = 0;
    int right = vec.size()-1;

    int result = -1;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while(left <= right)
    {
        int mid = (left+right)/2;
        if(vec[mid]>target)
            right = mid - 1;
        else if(vec[mid]<target)
            left = mid + 1;
        else { result = mid; break; }

    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout<<"Time difference = "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<"[us]"<<std::endl;
    std::cout<<"Time difference = "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()<<"[ns]"<<std::endl;

    std::cout<<"target found at "<<result<<"\n";

    begin = std::chrono::steady_clock::now();

    for(int i=0; i<vec.size(); i++)
        if(vec[i] == target)
            result = i;

    end = std::chrono::steady_clock::now();
    std::cout<<"Time difference = "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<"[us]"<<std::endl;
    std::cout<<"Time difference = "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()<<"[ns]"<<std::endl;

    // what is the time complexity of the binary search
    // question is how many times it is needed to divide N by 2 to get 1. This is actually binary search
    // 1 = N / 2^x
    // 2^x = N
    // log2(2^x) = log2(N)
    // x = log2(N)
    // this means you have to divide log N until you found your element



    return 0;
}