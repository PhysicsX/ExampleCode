#include <iostream>
#include <vector>
#include <unordered_map>

// 11. Container With Most Water
// if height[left] < height[right] then
// move forward from left to right. Because you have
// already the area which is bigger then right ones.
// if(height[i] < height[j])
// A = A(i,j) = (j-i)*min(height[i], height[j])
// A' = A(i, j-1) = (j-1-i)*(min(height[i], height[j]))
// for if height[i] < height [j-1]
// A' = (j-1-i)*height[i] which is smaller than (j-i)*height[i] = A
// A' < A

class Solution {
public:
    int maxArea(std::vector<int>& height) {
        
        int result {0};
        int area {0};
        int minHeight {0};
        size_t l {0};
        size_t r {height.size()-1};
        
        while(l < r)
        {
            minHeight = std::min(height[l], height[r]);
            area = (r-l)*minHeight;
            
            result = std::max(area, result);
            
            if(height[l]<height[r])
                l++;
            else
                r--;
        }
                    
        return result;
        
    }
};

int main()
{
    std::vector<int> vec {1,8,6,2,5,4,8,3,7};

    std::cout<<Solution{}.maxArea(vec);

    return 0;
}