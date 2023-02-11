#include <iostream>
#include <vector>


/*
 * It is like finding a start point of circle in linked list
 * Start point of the circle is the first repeated number
 * Lets define array like linked list with using index 
 * 1 3 4 2 2 (vector itself)
 * 0 1 2 3 4 (index)
 *
 * 0 goes to 1, 1 goies to 3, 3 goes to 2,
 * 0 -> 1 -> 3 -> 2 -> 4
 * 4 -> 2, as it is seen there is a loop between 2 and 4.
 * And the 2 is the start point of the circle which is
 * first repeated number in the array/vector.
 *
 *
*/

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
