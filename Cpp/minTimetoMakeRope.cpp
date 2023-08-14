#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>

// 1578. Minimum Time to Make Rope Colorful

// Base idea - What is the accumulation of elements minus maximum one
// Greedy approach can be used. Choose maximum element at each step
// to find overall maximum element in the array.
// compare current array and maxElement then add the min one into variable
// compare current and maxElement then keep maxElement
// repeat process

// Greedy algorithm is any algorithm that follows the problem
// solving heuristic of making the locally optimal choice at each
// stage

// int maxElement = 0, result = 0;
// for(int i=0; i<vec.size(); ++i)
// {
//  res += std::min(maxElement, vec[i]);
//  maxElement = std::max(maxElement, vec[i]);
// }
// return res;


class Solution
{
    public:
        int minCost(std::string& colors, std::vector<int>& neededTime)
        {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(NULL);
            std::cout.tie(NULL);
            
            int res = 0, currMax = 0;
            for(int i=0; i<colors.size(); ++i)
            {
                // set currMax to zero when colors are change
		// because same colorful ballons is different array
		// It is needed to find max and do not add to result
		if(i>0 && colors[i] != colors[i-1])
                {
                    currMax = 0;
                }

                res += std::min(currMax, neededTime[i]);
                currMax = std::max(currMax, neededTime[i]);
            }

            return res;;
        }

        // stupid solution
        // try to use "Minimnum movement for 3 identical consecutive letters"
        // find consecutive elements then process these elements one by one]
        // this will give time exceed because while loop inside for loop
        int minCostTimeExceed(std::string colors, std::vector<int>& neededTime) {
            unsigned int res = 0;

            auto size = colors.size();

            for(int i = 0; i < size;)
            {
                int j = i + 1;
                bool flag =false;
                while(j < size && (colors[j] == colors[i]))
                {
                    j++;
                    flag = true;
                }

                int k = i;
                int l = j -1;
                while(flag == true && k<l)
                {
                    auto it = std::min_element(std::begin(neededTime) + i, std::begin(neededTime) + j);
                    int indexSmallestEl = std::distance(std::begin(neededTime), it);
                    res = res + neededTime[indexSmallestEl];
                    neededTime[indexSmallestEl] = INT_MAX;
                    k++;
                }

                i = j;
            }
            return res;
        }
};

int main()
{
    std::string str {"abaac"};
    std::vector<int> vec {1,2,3,4,5};
    std::cout<<Solution{}.minCost(str, vec);
}
