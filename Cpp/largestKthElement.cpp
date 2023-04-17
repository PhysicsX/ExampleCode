#include <iostream>
#include <vector>
#include <utility>

class Solution
{
        /*
        The algorithm for finding the k-th largest element in an unsorted array is based 
        on the QuickSelect algorithm, which is a modification of the QuickSort algorithm. 
        The idea is to repeatedly partition the input array and narrow down the search space 
        based on the k-th largest element's position relative to the partition index.
    
        Choose a pivot element. In this implementation, the pivot element is always the first 
        element of the current search space (i.e., nums[left]).
        
        Perform a partition operation. Rearrange the elements in the search space such that 
        elements greater than the pivot come before the pivot, and elements less than the pivot 
        come after it. The partition function returns the final index of the pivot element.
        
        Compare the returned pivot index to k - 1:
        
        a. If the pivot index is equal to k - 1, we found the k-th largest element, and the algorithm terminates.
        b. If the pivot index is less than k - 1, the k-th largest element lies in the right partition. Update the left pointer to pivotIndex + 1 and repeat the process.
        c. If the pivot index is greater than k - 1, the k-th largest element lies in the left partition.
        Update the right pointer to pivotIndex - 1 and repeat the process.
        
        This process continues until the pivot index is equal to k - 1, at which point the k-th largest 
        element is found and returned.
    */

    public:
        int findKthLargest(std::vector<int>& nums, int k)
        {
            int left = 0, right = nums.size()-1, kth;
            while(true)
            {
                int idx = partition(nums, left, right);
                if(idx == k-1)
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
                    std::swap(nums[l++], nums[r--]);
                }
                if(nums[l] >= pivot)
                {
                    l++;
                }
                if(nums[r] <= pivot)
                {
                    r--;
                }
            }
            std::swap(nums[left], nums[r]);
            return r;
        }
};

int main() {

    std::vector<int> vec {3,2,1,5,6,4};

    std::cout<<Solution{}.findKthLargest(vec, 2);

    std::cout << std::endl;

    return 0;
}