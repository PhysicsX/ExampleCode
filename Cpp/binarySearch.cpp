#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <chrono>

int main()
{
    size_t size {1000};

    std::vector<int> numbers(size);
    std::generate(numbers.begin(), numbers.end(),[size](){

        static std::mt19937 rng(std::time(nullptr));
        return std::uniform_int_distribution<>(1,size)(rng);

    });

    std::cout<<"Numbers:\n";

    std::copy(numbers.begin(), numbers.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout<<std::endl;

    std::sort(numbers.begin(), numbers.end());
    numbers.erase(std::unique( numbers.begin(), numbers.end()), numbers.end());

    std::cout<<"After sort and removed duplicates\n";
    std::copy(numbers.begin(), numbers.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout<<std::endl;

    const auto target {55}; 
    auto left {0};
    auto right {numbers.size()-1};

    int result = -1;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // while(left <= right) // while(1) ?
    // {
    //     const auto mid {(left+right)/2};
    //     if(numbers[mid]>target)
    //         right = mid - 1;
    //     else if(numbers[mid]<target)
    //         left = mid + 1;
    //     else { result = mid; break; }
    // }
     
    while(left < right)
    {
        // const auto mid {left + (right-left)/2};
        // const auto mid {(left+right)/2};
        const auto mid {(left & right)+ ((left ^ right )>>1)};
        if(numbers[mid]>=target)
            right = mid;
        else if(numbers[mid]<target)
            left = mid + 1;
    }
    result = left;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout<<"Time difference = "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<"[us]"<<std::endl;
    std::cout<<"Time difference = "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()<<"[ns]"<<std::endl;

    std::cout<<"target found at "<<result<<"\n";

    begin = std::chrono::steady_clock::now();

    for(size_t i {0}; i<numbers.size(); i++)
        if(numbers[i] == target)
            result = i;

    end = std::chrono::steady_clock::now();
    std::cout<<"Time difference = "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<"[us]"<<std::endl;
    std::cout<<"Time difference = "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()<<"[ns]"<<std::endl;

    // what is the time complexity of the binary search (log(N))
    // question is how many times it is needed to divide N by 2 to get 1. This is actually binary search
    // 1 = N / 2^x
    // 2^x = N
    // log2(2^x) = log2(N)
    // x = log2(N)
    // this means you have to divide log N until you found your element

    return 0;
}