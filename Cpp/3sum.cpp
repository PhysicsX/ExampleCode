#include <iostream>
#include <vector>
#include <algorithm>

// 15. 3Sum
class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        
        std::vector<std::vector<int>> result;
        
        std::sort(nums.begin(), nums.end());
        
        for(size_t i {0}; i < nums.size(); i++)
        {
            int front = i + 1;
            int back = nums.size() - 1;
            
            while(i+1 < nums.size() && nums[i+1] == nums[i])
                i++;
            
            while(front < back)
            {
                int sum = nums[i] + nums[front] + nums[back];
                
                if(sum < 0)
                    front ++;
                else if(sum > 0)
                    back --;
                else
                {
                    result.push_back({nums[i], nums[front], nums[back]});
                    while(front<back && nums[front] == nums[front + 1]) front++;
                    while(front<back && nums[back] == nums[back - 1]) back--;
                    front ++; back --;
                }
            }
        }
        return result;
    }
};

int main(){
    
    std::vector<int> vec {-1,0,1,2,-1,-4};

    for(auto s: Solution{}.threeSum(vec))
    {
        for(auto c : s)
            std::cout<<c<<" ";
        
        std::endl(std::cout);
    }
}