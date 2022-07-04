#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Given a 0-indexed integer array nums of size n, 
// find the maximum difference between nums[i] and nums[j] 
// (i.e., nums[j] - nums[i]), such that 0 <= i < j < n and nums[i] < nums[j].
// using Kadane's Algorithm

class Solution {
public:
    int maximumDifference(const std::vector<int>& nums) {
        int currentMax {0};
        int resultMax {-1};
        
        for (size_t i {0}; i < nums.size()-1; i++) {
            int diff = nums[i+1]-nums[i];
            if (diff == 0) continue;
            currentMax = std::max(diff + currentMax, diff);
            resultMax = std::max(resultMax, currentMax);
        }
        
        return resultMax < 0 ? -1 : resultMax;
    }
};

template <
    class result_t   = std::chrono::microseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}
 
int main()
{    
    // test with small data set
    std::vector<int> vec { 1, 3, 4, 6, 2, 5};
    std::cout << "Maximum difference is " << Solution().maximumDifference(vec);
    std::cout<<std::endl;

    // generate vector with 0 - 9999
    std::vector<int> v;
    for(int i{1}; i<10000; i++)
    {
        v.push_back(i);    
    }
    
    // shffle generated vector
    auto rng {std::default_random_engine {}};
    std::shuffle(std::begin(v), std::end(v), rng);

    // with kadane's algorithm o(n)
    auto start {std::chrono::steady_clock::now()};
    int resKadane = Solution().maximumDifference(v);
    auto passedTime {since(start).count()};
    std::cout << "Maximum difference is with kadane's algorithm ";    
    std::cout << resKadane <<std::endl;
    std::cout << "Elapsed(us)=" << passedTime << std::endl;
    std::cout<<std::endl;
    
    // with sort (nlogn)
    std::vector<int> vecCopy = v;
    int resultSort {0};
    start = std::chrono::steady_clock::now();    
    std::sort(vecCopy.begin(), vecCopy.end());
    resultSort = vecCopy[vecCopy.size()-1] - vecCopy[0];
    passedTime = since(start).count();
    std::cout << "Maximum difference is with sort ";    
    std::cout<<resultSort<<std::endl;
    std::cout << "Elapsed(us)=" << passedTime << std::endl;
    std::cout<<std::endl;

    // with (n2)
    int result {0};
    start = std::chrono::steady_clock::now();
    for(size_t i{0}; i<v.size(); i++)
    {
        for(size_t j{0}; j<v.size(); j++)
        {
            result = std::max(result, v[j] - v[i]);
        }
    }
    passedTime = since(start).count();
    std::cout << "Maximum difference is with n2 ";    
    std::cout<<result<<std::endl;
    std::cout << "Elapsed(us)=" << passedTime << std::endl;

    return 0;
}
