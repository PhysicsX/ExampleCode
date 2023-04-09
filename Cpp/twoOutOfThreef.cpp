#include <vector>
#include <iostream>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoOutOfThree(std::vector<int>& nums1, std::vector<int>& nums2, std::vector<int>& nums3) {
        struct found
        {
            bool n1;
            bool n2;
            bool n3;
        };

        std::unordered_map<int, found> map;
        for(auto n : nums1) map[n].n1 = true;
        for(auto n : nums2) map[n].n2 = true;
        for(auto n : nums3) map[n].n3 = true;

        std::vector<int> result;
        result.reserve(map.size());
        
        for(const auto x : map)
        {
            if(x.second.n1 + x.second.n2 + x.second.n3 >= 2)
                result.push_back(x.first);
        } 

        return result;
    }
};

int main()
{
    std::vector<int> vec1 {3,1};
    std::vector<int> vec2 {2,3};
    std::vector<int> vec3 {1,2};

    for(const auto v : Solution{}.twoOutOfThree(vec1, vec2, vec3))
        std::cout<<v<<" ";

    return 0;
}