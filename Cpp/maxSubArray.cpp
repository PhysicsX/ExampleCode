#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        
        int largestSum = nums[0]; //SHRT_MIN;
        int sum = nums[0]; //SHRT_MIN;

        for(int i=0; i<nums.size(); ++i)
        {
            sum = std::max(nums[i], nums[i]+sum);
            
            largestSum = std::max(largestSum, sum);
             
        }

        return largestSum;     
    }
};


int main()
{
    std::vector<int> vec {-2,1,-3,4,-1,2,1,-5,4};

    std::cout<<Solution{}.maxSubArray(vec)<<std::endl;
}