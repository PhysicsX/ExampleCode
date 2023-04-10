#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> majorityElement(std::vector<int>& nums) {
        std::unordered_map<int, int> map;
        for(auto num : nums)
        {
            map[num] ++;
        }

        std::vector<int> result;
        result.reserve(map.size());
        for(const std::pair<int, int>& p : map)
        {
            if(p.second > nums.size()/3)
                result.push_back(p.first);
        }
        return result;
    }
};

int main()
{
    std::vector<int> vec {3,2,3};

    for(auto v : Solution{}.majorityElement(vec))
        std::cout<<v<<" ";

}