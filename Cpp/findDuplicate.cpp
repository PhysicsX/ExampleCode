#include <iostream>
#include <vector>

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[nums[0]];
        
        while(slow != fast)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        
        slow = 0;
        while(slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        
        return slow;
    }
};

int main()
{
	std::vector<int> vec {1,3,4,2,2};
	std::cout<<Solution{}.findDuplicate(vec)<<std::endl;

	return 0;
}
