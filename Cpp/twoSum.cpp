#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>
// 1. Two Sum

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
     
        std::unordered_map<int, int> map;
        
        for(size_t i{0}; i<nums.size(); i++)
        {
            auto it {map.find(target - nums[i])};
            if(it!= map.end())
                return std::vector<int>{static_cast<int>(i), it->second};
            
            map[nums[i]] = i;
        }
        return std::vector<int>{};
    }
};

int main(){
    std::vector<int> vec{2,7,11,15};
    auto res = Solution{}.twoSum(vec, 9);
    std::copy(res.begin(),res.end(),std::ostream_iterator<int>(std::cout, " " ));

}