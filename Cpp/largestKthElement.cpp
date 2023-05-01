#include <vector>
#include <algorithm>
#include <iostream>

// finding kth largest element is based on quick select
// algorithm which is based on quick sort algorithm
// The idea is to repeadetly partition the input array and
// narrow down the search space based on kth largest elements
// position relative to the partition index.

/*
    1. choose pivot element. In this example, the pivot element is 
    always the first element of the current search space(nums[left])
    2. Perform a partition operation. Rearrange the elements in the search
    space such that elements greater than the pivot come before the pivot,
    and the elements less than the pivot come after it. The partition funciton
    returns the final index of the pivot element.
    3. Compare the returned  pivot index to k-1:
        a. if the pivot index is equal to k-1, we found kth largest
        element and the algortihm terminates.
        b. If the pivot index is less than k-1, the kth largest eleemnt
        lies in the right partition. Update the left pointer to idx+1 and
        repeat the process.
        c. If the pivot index is greater than k-1, the kth largest element
        lies in the left partition. Update the left pointer to idx-1 and 
        repeat the process.
*/

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        int left = 0, right = nums.size() - 1, kth;
        while(true)
        {
            int idx = partition(nums, left, right);
            if(idx == k - 1)
            {
                kth = nums[idx];
                break;
            }
            if(idx < k - 1)
            {
                left = idx + 1;
            }
            else
            {
                right = idx - 1;
            }
        }
        return kth;
    }

private:
    int partition(std::vector<int>& nums, int left, int right)
    {
        int pivot = nums[left], l = left + 1, r = right;
        while(l <= r)
        {
            if(nums[l] < pivot && nums[r] > pivot)
            {
                std::swap(nums[l], nums[r]);
            }

            if(nums[l] >= pivot)
                l++;

            if(nums[r] <= pivot)
                r--;
        }
        std::swap(nums[left], nums[r]);
        return r;
    }


};

int main()
{
    std::vector<int> vec{3,4,5,1,2,0,3,12,3,4,5,6,8,7,4};

    std::cout<<Solution{}.findKthLargest(vec, 3)<<std::endl;

    return 0;
}