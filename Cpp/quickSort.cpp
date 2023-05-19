#include <iostream>
#include <vector>
#include <algorithm>

/*
    idea is that choose a pivot (can be done randomly or choosing from left/right)
    define left and right element. In the beginning left is 0 and right is size of the vector
    Iterate through left to right. according to pivot elements value, swap the iterated element such that
    if it is greater than the pivot value the swap with index which can be choosen from left or right.
    The idea is to collect the elements which are greater than the pivot to the right and smaller than to 
    left.
    Recursion can be used to make continue this process. Pivot should be replacted at the end when iteration
    is finished for each partioning.
*/

int partition(std::vector<int>& vec, int left, int right)
{
    int pivot = vec[left];
    int index = left + 1;

    for(int i = left + 1; i <= right; i++)
    {
        if(vec[i] < pivot) // condition for descending or ascanding order
        {
            std::swap(vec[i], vec[index++]);
        }
    }
    std::swap(vec[left], vec[index - 1]);
    return index - 1;
}

int partition2(std::vector<int>& vec, int left, int right)
{
    int pivot = vec[right];
    int index = left - 1;

    for(int i=left; i < right; ++i) // pivot is excluded intentionally i < right not i <= right. (both conditions are corrects)
    {
        if(vec[i] < pivot)
        {
            index ++;
            std::swap(vec[index], vec[i]);
        }
    }

    std::swap(vec[right], vec[index + 1]);

    return index + 1;
}

void quickSort(std::vector<int>& vec, int low, int high)
{
    if(low < high)
    {
        int pivotIndex = partition2(vec, low, high);
        quickSort(vec, low, pivotIndex - 1);
        quickSort(vec, pivotIndex + 1, high);
    }
}

int main()
{
    std::vector<int> nums = {3,1,4,2,9,5,6,7};

    quickSort(nums, 0, nums.size() - 1);

    std::cout << "Sorted array: ";
    for (int i = 0; i < nums.size(); i++) {
        std::cout << nums[i] << " ";
    }

}