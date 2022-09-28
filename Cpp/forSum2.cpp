#include <iostream>
#include <vector>
#include <unordered_map>

// leetcode 454. 4Sum II
// Given four integer arrays v1, v2, v3, and v4 all of length n, return the number of tuples (i, j, k, l) such that:
// 0 <= i, j, k, l < n
// nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

class Solution
{
    using vec = const std::vector<int>;
    public:
        int fourSumCount(vec& v1, vec& v2, vec& v3, vec& v4)
        {
            unsigned int result {0};

            std::unordered_map<int, int> map;

            size_t size = v1.size();

            for(int i{0}; i<size; i++)
                for(int j{0}; j<size; j++)
                    map[v1[i] + v2[j]]++;

            for(int i{0}; i<size; i++)
                for(int j{0}; j<size; j++)
                    result = result + map[-(v3[i] + v4[j])];

            return result;
        }
};

int main()
{
    std::vector<int> vec1 {1,2};
    std::vector<int> vec2 {-2,-1};
    std::vector<int> vec3 {-1,2};
    std::vector<int> vec4 {0,2};

    std::cout<<Solution{}.
    fourSumCount(vec1, vec2, vec3, vec4)<<std::endl;

    return 0;
}