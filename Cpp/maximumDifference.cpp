#include <iostream>
#include <vector>

// Given a 0-indexed integer array nums of size n, 
// find the maximum difference between nums[i] and nums[j] 
// (i.e., nums[j] - nums[i]), such that 0 <= i < j < n and nums[i] < nums[j].
// using Kadane's Algorithm

class Solution {
public:
    int maximumDifference(std::vector<int>& nums) {
        int currentMax {0};
        int resultMax = {-1};
        
        for (size_t i = 0; i < nums.size()-1; i++) {
            int diff = nums[i+1]-nums[i];
            if (diff == 0) continue;
            currentMax = std::max(diff + currentMax, diff);
            resultMax = std::max(resultMax, currentMax);
        }
        
        return resultMax < 0 ? -1 : resultMax;
    }
};
 
int main()
{
    std::vector<int> vec {80, 2, 6, 3, 100};
    std::cout << "Maximum difference is " << Solution().maximumDifference(vec);
 
  return 0;
}
