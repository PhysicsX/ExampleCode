#include <iostream>
#include <vector>
#include <algorithm>

int partition(std::vector<int>& vec, int left, int right)
{
    int pivot = vec[left];
    int index = left + 1;

    for(int i = left + 1; i <= right; i++)
    {
        if(vec[i] < pivot)
        {
            std::swap(vec[i], vec[index]);
            index ++;
        }
    }
    std::swap(vec[left], vec[index - 1]);
    return index - 1;
}

void quickSort(std::vector<int>& vec, int low, int high)
{
    if(low < high)
    {
        int pivotIndex = partition(vec, low, high);
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