#include <iostream>
#include <algorithm>
#include <vector>

class Solution
{
    public:
        int minCost(std::string& colors, std::vector<int>& neededTime)
        {
            int res = 0, currMax = 0;
            for(int i=0; i<colors.size(); ++i)
            {
                if(i>0 && colors[i] != colors[i-1])
                {
                    currMax = 0;
                }

                res += std::min(currMax, neededTime[i]);
                currMax = std::max(currMax, neededTime[i]);
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