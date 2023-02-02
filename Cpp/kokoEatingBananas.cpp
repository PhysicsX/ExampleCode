#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    long long findSuitableHour(const std::vector<int>& piles, int target)
    {
         long long currPile = 0;
         long long hours = 0;
         for(unsigned int i = 0; i < piles.size(); i++)
         {
            const auto& currPile = piles[i];

            if(currPile > target)
            {
                hours += currPile / target;   
                if(currPile % target != 0) hours++;
            }
            else if(currPile <= target)
            {
                hours ++;
            }
         }
         return hours;        
    }
    
    int minEatingSpeed(std::vector<int>& piles, int h) {

        int l=1, r= *max_element(piles.begin(),piles.end());;

        while(l < r)
        {
            // auto mid = l + (r-l)/2;
            auto mid = (l + r) >> 1;

            if(findSuitableHour(piles, mid) <= h) r = mid;
            else l = mid + 1;
        }

        return l;
    }    
};

int main()
{
	std::vector<int> vec {30,11,23,4,20};
	std::cout<<Solution{}.findSuitableHour(vec, 6)<<std::endl;
}


